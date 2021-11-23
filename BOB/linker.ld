OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
PHDRS {
  headers PT_PHDR PHDRS;
  interp PT_INTERP;
  text PT_LOAD FILEHDR PHDRS;
  data PT_LOAD;
  dynamic PT_DYNAMIC;
}
SECTIONS {
  . = SIZEOF_HEADERS;
  ImageBase = .;
  .text : ALIGN(0x1000) { *(.text) } :text
  .data : ALIGN(0x1000) { *(.data) } :data
  .rodata : ALIGN(0x1000) { *(.rodata) }
  .bss : ALIGN(0x1000) {
      *(COMMON)
      *(.bss)
  }
}