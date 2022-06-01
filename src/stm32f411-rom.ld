ENTRY(reset_handler)

MEMORY
{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 512K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 128K
}


SECTIONS
{
    /* Esta secao deve incluir a secao .text de todos arquivos objeto de entrada */
    .text :
    {
        /* combinar todas as secoes .isr_vectors de todos arquivos de entrada */
        /* combinar todas as secoes .text de todos arquivos de entrada */
        /* combinar todas as secoes .rodata de todos arquivos de entrada */
    }>(vma) AT>(lma)

    /* Esta secao deve incluir a secao .data de todos arquivos objeto de entrada */
    .data :
    {

    }>(vma) AT>(lma)

    /* Esta secao deve incluir a secao .bss de todos arquivos objeto de entrada */
    .bss :
    {
        
    }
}