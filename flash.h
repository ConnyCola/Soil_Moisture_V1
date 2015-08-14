#ifndef FLASH_H
#define FLASH_H

void erase_flash(int addr);
void write_flash_float(float val_vref_l, float val_vref_h, float val_vcc);
float read_flash_float(int addr);

#endif