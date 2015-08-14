#ifndef FLASH_H
#define FLASH_H

void erase_flash(int addr);
void write_flash_float(int addr, float value);
float read_flash_float(int addr);

#endif