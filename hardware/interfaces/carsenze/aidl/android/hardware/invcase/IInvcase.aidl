package android.hardware.carsenze;

@VintfStability
interface ICarSenze {
   String getCpuStats();
   String getMemoryStats();
   String getNetworkStats();
}