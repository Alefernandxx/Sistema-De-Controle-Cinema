# Sistema de Controle de Cinema

Sistema em linguagem C desenvolvido para gerenciar sessões, salas e reservas de poltronas de um cinema via terminal, aplicando conceitos de estruturas heterogêneas (`struct`), manipulação de ponteiros e passagem de parâmetros por valor e por referência.

---

## Funcionalidades

- **Listagem de Sessões:** Exibição detalhada de filmes, datas, horários e salas disponíveis.
- **Mapa da Sala:** Visualização em tempo real das poltronas livres (`[n]`) e ocupadas (`[Xn]`).
- **Compra de Poltronas:** Validação e reserva de assentos por fileira (`A`, `B`, `C`) e número (`1` a `5`).
- **Cancelamento de Reserva:** Liberação de assentos previamente ocupados.
- **Validação de Conflitos:** Bloqueio de compras duplicadas e cancelamentos em poltronas já desocupadas.

---

## Estrutura do Projeto

```text
CinemaTrabalho/
├── .gitignore
├── Cinema.c
└── README.md
