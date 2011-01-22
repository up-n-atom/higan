struct HuC1 : MMIO {
  bool ram_enable;   //0000-1fff
  uint8 rom_select;  //2000-3fff
  uint8 ram_select;  //4000-5fff

  uint8 mmio_read(uint16 addr);
  void mmio_write(uint16 addr, uint8 data);
  void power();
} huc1;