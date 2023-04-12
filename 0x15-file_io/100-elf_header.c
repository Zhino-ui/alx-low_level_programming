#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

/*
 * check_elf - check if ELF file
 * @e_ident: a pointer
 * Description: exit(98) if not elf file
 */

void check_elf(unsigned char *e_ident)
{
	int ind;

	for (ind = 0; ind < 4; ind++)
	{
		if (e_ident[ind] != 127 &&
			e_ident[ind] != 'E' &&
			e_ident[ind] != 'L' &&
			e_ident[ind] != 'F')
		{
			dprintf(STDERR_FILENO, "error: not an elf file\n");
			exit(98);
		}
	}
}

/*
 * print_magic - printy magic numbers
 * @e_ident: a pointer
 * Description: numbers are spaced out
 */

void print_magic(unsigned char *e_ident)
{
	int ind;

	printf(" Magic: ");
	for (ind = 0; ind < EI_NIDENT; ind++)
	{
		printf("%02x", e_ident[ind]);

		if (ind == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/*
 * print_class - outputs elf header class
 * @e_ident: a pointer
 */

void print_class(unsigned char *e_ident)
{
	printf(" class:	");

	switch (e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf("none\n");
			break;
		case ELFCLASS32:
			printf("ELF32\n");
			break;
		case ELFCLASS64:
			printf("ELF64\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/*
 * print_data- print data
 * @e_ident: pointer
 */

void print_data(unsigned char *e_ident)
{
	printf(" Data:	");

	switch (e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("little endian\n");
		break;
	case ELFDATA2MSB:
		printf("big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/*
 * print_version -print version
 */

void print_version(unsigned char *e_ident)
{
	printf(" Version:	%d",
		e_ident[EI_VERSION]);

	switch (e_ident[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/*print_osabi- prints os/abi
 * @e_ident: pointer
 */

void print_osabi(unsigned char *e_ident)
{
	printf(" OS/ABI:	");

	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("unix -sytem V\n");
		break;
	case ELFOSABI_HPUX:
		printf("unix_ hp-ux\n");
		break;
	case ELFOSABI_NETBSD:
		printf("unix - nestbsd\n");
		break;
	case ELFOSABI_LINUX:
		printf("unix - linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("unix - solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("unix - irix\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("unix - freebsd\n");
		break;
	case ELFOSABI_TRU64:
		printf("unix - tru64\n");
		break;
	case ELFOSABI_ARM:
		printf("arm\n");
		break;
	case ELFOSABI_STANDALONE:
		printf(" standalone\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/*
 * print_abi- prints abi
 * @e_ident: pointer
 */

void print_abi(unsigned char *e_ident)
{
	printf(" ABI VERSION:	%d\n",
		e_ident[EI_ABIVERSION]);
}

/*print_type - prints type of elf header
 * @e_type- elf type
 */

void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_type >>= 8;
	}
	printf(" type:	");

	switch (e_type)
	{
		case ET_NONE:
			printf("none\n");
			break;
		case ET_REL:
			printf("relocateble file\n");
			break;
		case ET_EXEC:
			printf("executable\n");
			break;
		case ET_DYN:
			printf("dynamic file\n");
			break;
		case ET_CORE:
			printf("root file\n");
			break;
		default:
			printf("unknown: %x>\n", e_type);
	}
}

/*print_entry - prints entry point
 * @e_entry: the address
 * @e_ident: pointer
 */

void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf(" Entry point address:	");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			((e_entry >> 8) && 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);
	else
		printf("%#lx\n", e_entry);
}

/*
 * close_elf - closes file
 * @elf: file
 * description: exit(98) if cannot be closed
 */

void close_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: cannot close fd %d\n", elf);
		exit(98);
	}
}


/*
 * main - copy contents of a file into anothe file
 * @argc: arguments numer
 * @argv: array
 * Return: 0 on success
 * Description: exit(98) if code fails
 */

int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int op, re;

	op = open(argv[1], O_RDONLY);
	if (op == -1)
	{
		dprintf(STDERR_FILENO, "Error: cannot read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
       if (header == NULL)
       {
		close_elf(op);
		dprintf(STDERR_FILENO, "Error: cannot read file %s\n", argv[1]);
		exit(98);
       }
       re = read(op, header, sizeof(Elf64_Ehdr));
       if (re == -1)
       {
	       free(header);
	       close_elf(op);
	       dprintf(STDERR_FILENO, "Error: `%s`: no such file\n", argv[1]);
	       exit(98);
       }

       check_elf(header->e_ident);
       printf("ELF header:\n");
       print_magic(header->e_ident);
       print_class(header->e_ident);
       print_data(header->e_ident);
       print_version(header->e_ident);
       print_osabi(header->e_ident);
       print_abi(header->e_ident);
       print_type(header->e_type, header->e_ident);
       print_entry(header->e_entry, header->e_ident);

       free(header);
       close_elf(op);
       return (0);
}



