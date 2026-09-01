# Sistema de Controle de Cinema

Sistema em linguagem C desenvolvido para gerenciar sessões, salas e reservas de poltronas de um cinema via terminal, aplicando conceitos de estruturas heterogêneas (`struct`), manipulação de ponteiros, passagem de parâmetros por valor e referência.

---

## Funcionalidades

- **Listagem de Sessões:** Exibição detalhada de filmes, datas, horários e salas disponíveis.
- **Mapa da Sala:** Visualização gráfica em tempo real das poltronas livres (`[n]`) e ocupadas (`[Xn]`).
- **Compra de Poltronas:** Validação e reserva de assentos por fileira (`A`, `B`, `C`) e número (`1` a `5`).
- **Cancelamento de Reserva:** Liberação de assentos previamente ocupados.
- **Tratamento de Conflitos:** Bloqueio de vendas duplicadas e cancelamentos de poltronas já livres.

---

## Conceitos Aplicados

- **Estruturas de Dados (`struct`):** Modelagem de `Poltrona`, `Sala`, `Data` e `Sessao`.
- **Passagem por Referência (Ponteiros):** Utilizada em funções que realizam mutação de estado (`cadastrarPoltrona`, `inicializarSala`, `cadastrarSessao`, `comprarPoltrona`, `cancelarCompra`).
- **Passagem por Valor:** Utilizada em funções de leitura e exibição (`mostrarPoltrona`, `mostrarMapaSala`, `mostrarData`, `mostrarSessao`).

---

## Como Compilar e Executar

### Pré-requisitos
- Compilador C (ex.: `gcc`, `clang` ou `MinGW` no Windows).

### Compilação
Abra o terminal no diretório do projeto e execute:

```bash
gcc src/main.c -o cinema