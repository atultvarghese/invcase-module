package android.hardware.carsenze;

@VintfStability
interface ICarsenze {
   String getCpuStats();
   String getMemoryStats();
   String getNetworkStats();
}