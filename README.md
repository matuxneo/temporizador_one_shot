# Atividade 2: Temporizador de um disparo (One Shot). 

## Descrição
Com o emprego da função add_repeating_timer_ms(), presente na ferramenta Pico SDK, projete um semáforo com temporização de 3 segundos para cada alteração de sinal. O
fluxograma simplificado de atuação do semáforo está na figura 1. O código está localizado no arquivo `matrizrgbtarefa.c`.

## Como Rodar o Projeto

Para rodar o projeto localmente, siga os seguintes passos:

### 1. Clone o repositório:
```sh
 git clone https://github.com/matuxneo/temporizador_one_shot.git
```

### 2. Entre na pasta do projeto:
```sh
 cd temporizador_one_shot
```

## Instruções para Configuração e Compilação do Projeto

### Passo 1: Baixar o Vscode
Acesse a página oficial do Vscode:
[Download](https://code.visualstudio.com/docs/?dv=win64user)

- Baixe o arquivo mais recente para Windows .
- Prossiga com a instalação parão.

### Passo 2: Instale a extensão Raspberry Pi Pico
[Download] (https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)

Depois de instalado, acesse o ícone da extensão do menu lateral correspondende ao Pi Pico:

1. Clique em **importar projeto**.
2. Vá em **Em Basic Settings** → **Escolha o local do arquivo baixado** → **clique em Import** (no lado direito).
6. Clique em **OK** em todas as janelas.

### Passo 3: Instale a extensão Wokwi Simulator
[Download] (https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode)


## Simulação no Wokwi

Após a configuração, você pode usar o simulador Wokwi para testar o circuito.
- Acesse o simulador através do link [Wokwi](https://wokwi.com/)
- Ou use a extensão do Wokwi no VSCode: [Wokwi VSCode](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode)

Veja como a interação com os botões aciona os LEDs e como os estados do semáforo são alternados automaticamente.

Após isso é só iniciar a simulação no wokwi integrado ao vs code.


