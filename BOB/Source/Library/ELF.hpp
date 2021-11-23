#ifndef ELFHeaders

struct ELFHeaders {
  unsigned char Identifier[16];
  unsigned short Type, Machine;
  unsigned int Version;
  unsigned long long Entry, ProgramHeaderOffset, SectionHeaderOffset;
  unsigned int Flags;
  unsigned short Size, ProgramHeaderEntrySize, ProgramHeaderEntries, SectionHeaderEntrySize, SectionHeaderEntries, SectionNameIndex;
  bool checkMagic() const { return (memcmp(Identifier, "\u007fELF\0", strlen("\u007fELF\0"))) == 0; }
  unsigned char getFileClass() const { return Identifier[4]; }
  unsigned char getDataEncoding() const { return Identifier[5]; }
};

#endif

#ifndef ELFProgramHeaders

struct ELFProgramHeaders {
  unsigned int Type, Flags;
  unsigned long long Offset, VirtualAddress, PhysicalAddress, FileSize, MemorySize, Alginment;
};

#endif

#ifndef ELFDynamicEntry

struct ELFDynamicEntry {
  long long int d_tag;
  union {
    unsigned long long int d_val, d_ptr;
  } d_un;
};

#endif

#ifndef ELFRelocationEntry

struct ELFRelocationEntry {
  unsigned long long int r_offset;
  unsigned long long int r_info;
  unsigned int getSymbol() const { return (r_info >> 32); }
  unsigned int getType() const { return (unsigned int)(r_info & 0xffffffffL); }
  void setSymbol(unsigned int s) { setSymbolAndType(s, getType()); }
  void setType(unsigned int t) { setSymbolAndType(getSymbol(), t); }
  void setSymbolAndType(unsigned int s, unsigned int t) { r_info = ((unsigned long long int)s << 32) + (t & 0xffffffffL); }
};

#endif