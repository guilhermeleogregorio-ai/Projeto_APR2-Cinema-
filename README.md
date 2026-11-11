# Sistema Cinema — Projeto APR2

Sistema de gerenciamento de cinema em C (salas, filmes e sessões), com persistência em arquivos binários. Projeto acadêmico.

## Rodar

```bash
# Compilar (GCC)
gcc main.c -o main

# Executar
./main        # Linux / macOS
main.exe      # Windows
```

Os arquivos `salas.dat`, `filmes.dat` e `sessoes.dat` são criados na mesma pasta do executável ao salvar os dados. Os relatórios são gerados em `.txt`.

## Fluxo (Tema 8: Cinema)

1. **Menu principal**: Salas, Filmes, Sessões, Relatórios ou Sair.
2. **Salas**: código (chave), nome, capacidade, tipo de exibição (ex.: 3D, IMAX) e acessibilidade (1 = sim, 0 = não).
3. **Filmes**: código (chave), nome, ano de lançamento, diretor e até 10 atores.
4. **Sessões**: código do filme + código da sala + data + horário (chave composta) e preço do ingresso. Só aceita filme e sala já cadastrados.
5. **CRUD em cada submenu**: listar todos, buscar por chave, incluir (sem repetição), alterar e excluir (com confirmação).
6. **Integridade**: não é possível excluir filme ou sala que tenham sessões vinculadas.
7. **Relatórios** (salvos em arquivo texto):
   - Salas por tipo de exibição e capacidade mínima → `relatorio_salas.txt`
   - Filmes lançados a partir de um ano → `relatorio_filmes.txt`
   - Sessões entre duas datas, com dados do filme, atores e sala → `relatorio_sessoes.txt`

## Estrutura

| Arquivo | Descrição |
| --- | --- |
| `main.c` | Código-fonte completo |
| `announcement.md` | Enunciado do projeto |
| `*.dat` | Arquivos binários de dados (gerados em execução) |
| `relatorio_*.txt` | Relatórios gerados |

## Conceitos aplicados

- `struct` para cada entidade (`Sala`, `Filme`, `Sessao`)
- Vetores dinâmicos com `realloc` para o armazenamento temporário
- Persistência com `fread` / `fwrite` em arquivos binários (um por entidade)
- Relatórios com `fprintf` em arquivos texto
- Datas e horários armazenados como inteiros (`AAAAMMDD` e `HHMM`) para facilitar comparações
- Funções separadas para cada operação

## Observações

- Datas no formato `DD/MM/AAAA` e horários no formato `HH:MM`.
- Projeto escrito em C, com fins acadêmicos.
