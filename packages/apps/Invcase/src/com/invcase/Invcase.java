package com.invcase;

import android.content.Context;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.hardware.invcase.IInvcase;
import android.widget.Toast;


public class Invcase extends Activity {
    private static final String TAG = "Invcase";
    private static final String IINVCASE_AIDL_INTERFACE = "android.hardware.invcase.IInvcase/default";
    private static IInvcase invcaseAJ; // AIDL Java

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = (Button)findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText editText = (EditText)findViewById(R.id.editText);
                String txt = editText.getText().toString();
                Log.d(TAG, "App: request= " + txt);

                if(invcaseAJ != null) {
                    try {
                        invcaseAJ.putChars(txt);
                         Log.e(TAG, "Put Chars called successfully");
                          String message = "Put Chars called successfully" + invcaseAJ;
                           Toast.makeText(Invcase.this, message, Toast.LENGTH_LONG).show();
                    } catch (android.os.RemoteException e) {
                        Log.e(TAG, "IInvcase-AIDL error", e);
                           String message = "put Chars error" + e;
                        Toast.makeText(Invcase.this, message, Toast.LENGTH_LONG).show();
                    }
                }

                String ret = "";

                if(invcaseAJ != null) {
                    try {
                        ret = invcaseAJ.getChars();
                           Log.e(TAG, "get Chars called successfully");
                             String message =" get Chars called successfully" + ret;
                           Toast.makeText(Invcase.this, message, Toast.LENGTH_LONG).show();
                    } catch (android.os.RemoteException e) {
                        Log.e(TAG, "IInvcase-AIDL error", e);
                          String message = "get Chars error" + e;
                        Toast.makeText(Invcase.this, message, Toast.LENGTH_LONG).show();
                    }
                }

                Log.d(TAG, "App: get= " + ret);

                TextView tv = (TextView)findViewById(R.id.textView);
                tv.setText(ret);
            }
        });

        IBinder binder = ServiceManager.getService(IINVCASE_AIDL_INTERFACE);
        if (binder == null) {
            Log.e(TAG, "Getting " + IINVCASE_AIDL_INTERFACE + " service daemon binder failed!");
        } else {
            invcaseAJ = IInvcase.Stub.asInterface(binder);
            if (invcaseAJ == null) {
                Log.e(TAG, "Getting IInvcase AIDL daemon interface failed!");
            } else {
                Log.d(TAG, "IInvcase AIDL daemon interface is binded!");
            }
        }
    }
}
