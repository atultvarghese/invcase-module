package android.hardware.invcase;

@VintfStability
interface IInvcase {
   String getCpuStats();
   String getMemoryStats();
   String getNetworkStats();
}