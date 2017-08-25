#include "mpr121.h"

extern void mpr121_init(void)
{
  // Section A
  // This group controls filtering when data is > baseline.
  write_i2c(touch_shield,MHD_R, 0x01);
  write_i2c(touch_shield,NHD_R, 0x01);
  write_i2c(touch_shield,NCL_R, 0x00);
  write_i2c(touch_shield,FDL_R, 0x00);

  // Section B
  // This group controls filtering when data is < baseline.
  write_i2c(touch_shield,MHD_F, 0x01);
  write_i2c(touch_shield,NHD_F, 0x01);
  write_i2c(touch_shield,NCL_F, 0xFF);
  write_i2c(touch_shield,FDL_F, 0x02);
  
  // Section C
  // This group sets touch and release thresholds for each electrode
  write_i2c(touch_shield,ELE0_T, TOU_THRESH);
  write_i2c(touch_shield,ELE0_R, REL_THRESH);
  write_i2c(touch_shield,ELE1_T, TOU_THRESH);
  write_i2c(touch_shield,ELE1_R, REL_THRESH);
  write_i2c(touch_shield,ELE2_T, TOU_THRESH);
  write_i2c(touch_shield,ELE2_R, REL_THRESH);
  write_i2c(touch_shield,ELE3_T, TOU_THRESH);
  write_i2c(touch_shield,ELE3_R, REL_THRESH);
  write_i2c(touch_shield,ELE4_T, TOU_THRESH);
  write_i2c(touch_shield,ELE4_R, REL_THRESH);
  write_i2c(touch_shield,ELE5_T, TOU_THRESH);
  write_i2c(touch_shield,ELE5_R, REL_THRESH);
  write_i2c(touch_shield,ELE6_T, TOU_THRESH);
  write_i2c(touch_shield,ELE6_R, REL_THRESH);
  write_i2c(touch_shield,ELE7_T, TOU_THRESH);
  write_i2c(touch_shield,ELE7_R, REL_THRESH);
  write_i2c(touch_shield,ELE8_T, TOU_THRESH);
  write_i2c(touch_shield,ELE8_R, REL_THRESH);
  write_i2c(touch_shield,ELE9_T, TOU_THRESH);
  write_i2c(touch_shield,ELE9_R, REL_THRESH);
  write_i2c(touch_shield,ELE10_T, TOU_THRESH);
  write_i2c(touch_shield,ELE10_R, REL_THRESH);
  write_i2c(touch_shield,ELE11_T, TOU_THRESH);
  write_i2c(touch_shield,ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  write_i2c(touch_shield,FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Enable 6 Electrodes and set to run mode
  // Set ELE_CFG to 0x00 to return to standby mode
  write_i2c(touch_shield,ELE_CFG, 0x0C);	// Enables all 12 Electrodes
  //write_i2c(touch_shield,ELE_CFG, 0x06);		// Enable first 6 electrodes
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*write_i2c(touch_shield,ATO_CFG0, 0x0B);
  write_i2c(touch_shield,ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   write_i2c(touch_shield,ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
  write_i2c(touch_shield,ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}
