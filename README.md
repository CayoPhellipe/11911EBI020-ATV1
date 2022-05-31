# ATV1: Configuração do ambiente de desenvolvimento bare metal

## Instruções

Siga os roteiros anexos para instalação e configuração do seu ambiente bare metal de desenvolvimento. Crie os arquivos básicos do seu primeiro programa (main.c, startup.c, linker script, Makefile). Teste todo o ambiente. Depois, crie um repositório na sua conta no github com o seguinte formato:

- **MATRICULA-ATV1**

Dentro do repositório, crie um arquivo README.md e descreva o trabalho realizado. Crie também um diretório src e coloque nele os arquivos do primeiro exemplo.

Atenção: o trabalho não será corrigido se não estiver com o padrão de nomes e diretórios pedidos.

# LAB1

## Objetivo da aula

Os objetivos dessa aula não foram todos realizados por mim, o roteiro se destina a utilização do _Windows Subsystem for Linux 2 (WSL2)_ configurado para o _Ubuntu 20.04_, porém, este já é o sistema operacional que utilizo, então os passos referentes as configuração do _WSL2_ não foram executados.

Instalar e configurar o Ubuntu 20.04 no Windows Subsystem for Linux 2 (WSL2)
como sistema para desenvolvimento de firmware para microcontroladores da
família STM32. Nesta aula aprenderemos a instalar
• Windows Subsystem for Linux 2;
• GCC - GNU C Compiler;
• GCC ARM Toolchain;
• OpenOCD - Open On Chip Debugger;
• Sistema de controle de versões Git, e;
• Microsoft Visual Studio Code.

Instalação de dispositivos USB no WSL2 e configuração da interface de programação e depuração de código ST-LINK.

## Instalação do GCC e Git

Foram instaladas algumas ferramentas básicas que serão utilizadas ao longo
do curso, o compilador _GCC - GNU C Compiler_ e ferramenta de controle
de versões _Git_. Para instalar estas ferramentas utilizamos o comando abaixo:

```
foo@bar$ sudo apt install build-essential git
```

Após finalizar o processo de instalação usamos o comando a seguir para verificar se o _gcc_ e o _git_ foram instalados
corretamente

```
foo@bar$ gcc --version
foo@bar$ git --version
```

Logo após, configuramos o _git_

```
foo@bar$ git config --global user.name "seu nome aqui"
foo@bar$ git config --global user.email "seu e-mail aqui"
```

## Instalçao GCC ARM Toolchain

Foi instalado o _GCC ARM Toolchain_ e descompactado através dos seguintes comandos

```
foo@bar$ wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.37
foo@bar$ sudo tar xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C /usr/share/
```

Para facilitar a utilização foram criados links simbólicos para as ferramentas do toolchain no _/usr/share/_

```
foo@bar$ sudo ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/* /usr/bin/
```

Baixamos também as dependencias nescessárias para utilização do _toolchain_

```
foo@bar$ sudo apt install libncurses-dev libtinfo-dev
foo@bar$ sudo ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.6 /usr/lib/x86_64-linux-gnu/libnfoo@bar$ sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtin
```

E testamos se o toolchain foi instalado correntamente por meio dos comandos:

```
foo@bar$ arm-none-eabi-gcc --version
foo@bar$ arm-none-eabi-g++ --version
foo@bar$ arm-none-eabi-gdb --version
```

## Instalação de ferramentas de gravação e depuração

Executamos a instalação da ferramenta OpenOCD, no diretório Downloads, através do github, versão 0.11.08, seguindo as linhas de comando abaixo

```
foo@bar$ git clone https://git.code.sf.net/p/openocd/code openocd-code
foo@bar$ cd openocd-codefoo@bar$ git tag
foo@bar$ git switch -c v0.11.08
foo@bar$ ./bootstrap
foo@bar$ ./configure --enable-stlink
foo@bar$ make
foo@bar$ sudo make install
foo@bar$ openocd --version
```

Se tudo ocorrer bem, a saída deverá ser similar a essa

```
Open On-Chip Debugger 0.11.0+dev-00693-g0a36acbf6 (2022-05-22-22:47)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
```

## Ferramentas do ST-Link

Instalamos ferramentas de código aberto do ST-Link que utilizaremos pra gravação e depuração similarmente ao OpenOCD, são elas:

- st-info- a programmer and chip information tool
- st-flash- a flash manipulation tool
- st-util- a GDB server (supported in Visual Studio Code / VSCodium via the Cortex-Debug plugin)

A instalação foi feita a partir do github da ferramenta, e salva no diretório Downloads

```
foo@bar$ git clone https://github.com/stlink-org/stlink stlink-tools
foo@bar$ sudo apt install git build-essential cmake libusb-1.0-0 libusb-1.0-0-dev
foo@bar$ cd stlink-tools
foo@bar$ git tag
foo@bar$ git switch -c v1.7.0
foo@bar$ make clean
foo@bar$ make releasefoo@bar$ sudo make install
foo@bar$ sudo ldconfig
```

Verificamos se as ferramentas stlinkforam instaladas corretamente

```
foo@bar$ st-flash --version
foo@bar$ st-info --version
foo@bar$ st-trace --version
foo@bar$ st-util --version
```

O ultimo passo da aula era a instalção do VSCode, não executei esse passo, já utilizo a IDE e já está baixada e configurada com as extensões no sistema linux.

- C/C++
- C/C++ Extension Pack
- C/C++ Themes
- Cortex-Debug

# LAB2

## Objetivo da aula

O objetivo desta aula era mostrar o processo de criação de todos os arquivos de partida e o processo de compilação para um sistema Cortex-M com o programa sendo desenvolvido do zero.
Neste laboratório foram abordados os seguintes temas:
• automação do processo de compilação utilizando o utilitário make;
• criação do arquivo startup.c para microcontroladores Cortex-M.

## Criação de um novo projeto

Inicialmente foi criado um arquivo [main.c](src/main.c) que a priori não executaria nenhuma atividade, apenas ficaria em looping sem encerrar o programa.

```
#include <stdlib.h>

int main(int argc, char *argv[])
{
    while(1){};
    /* Nao deveria chegar aqui */
    return EXIT_SUCCESS;
}
```

Para compilar este programa, foi ensinado que o compilador fornecido com o **GNU Arm Embedded Toolchain**, o compilador **_arm-none-eabi-gcc_**, poderia realizar esta tarefa, porém, o processo de linkedição para arquitetura ARM Cortex M precisam ser feitas de forma específica, então, as compilações serão feitas sem processo de linkagem, deixando essa etapa para o final. Para isso, utilizamos as opções `-c` para que não seja feita a etapa de linkagem e `-o` para que possamos especificar o nome do arquivo gerado como `main.o`. Passamos também a opção `-mcpu=cortex-m4` para especificar ao compilador a arquitetura que estamos usando e a opção `-mthumb` para trabalhar com o padrão 16bits.

```
foo@bar$ arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb main.c -o main.o
```

Para compilar todo o código, foi criado um arquivo [Makefile](src/Makefile) que ao longo da atividade foi sendo trabalhada modificações em seu conteúdo para automatizar o processo de compilação dos arquivos.

## Arquivo de inicialização

Desenvolver aplicações para estruturas sem sistema operacional é preciso definir algumas etapas para controle de memória que serão executados antes da **main()**, para isso, foi criado o arquivo [startup.c](src/startup.c).

De acordo com o modelo de memória do **STM32F411**, precisamos definir o _Stack Pointer_ (ou **SP**) na região final da memória **SRAM** para maximizar a memória **stack**, também é no modelo que descobrimos o início da **SRAM** em _0x20000000_.

É preciso definir também a organização dos vetores de interrupção no inicio da memória **FLASH** do programa, para que seu uso com outros sistemas periféricos seja utilizado adequadamente. Para isso, o Manual de Referencia do STM32F411 fornece toda a tabela de vetores de interrupção para serem configurados, inicializamos ele no arquivo [startup.c](src/startup.c).

É preciso garantir que o vetor de interrupções será armazenado no início da memória **FLASH**, essa etapa é feita na linkedição, e para isso, precisamos informar que seção o compilador irá posicinar no início da **FLASH** atribuindo o vetor a essa seção, chamamos de _.isr_vectors_.

Para funcionamento adequado do programa é nescessário uma rotina de _Reset Exception_, que será responsável por copiar a o conteúdo da seção _.data_ da memória **FLASH** para memória **SRAM** e inicializar a sessão _.bss_ em zero para garantir que as variáveis globais seguirão o padrão de inicialização com zero. Essa rotina foi chamada de _reset_handler()_.

# LAB3
