# Estrutura da Rede 



## Como é a clínica
É uma clínica fictícia de pequeno porte, com uma única unidade e sem filiais. Por isso a proposta de rede foi pensada para ser simples, segura e fácil de manter.

## Equipamentos propostos

As quantidades abaixo são um **exemplo de dimensionamento** para o cenário fictício, e não um levantamento real.

| Equipamento | Quantidade (exemplo) | Para que serve |
|---|---|---|
| Roteador com firewall | 1 | Liga a clínica à internet e filtra acessos indevidos |
| Switch | 1 | Conecta os computadores da rede cabeada |
| Access point (Wi-Fi) | 1 | Wi-Fi dos funcionários e Wi-Fi separado para visitantes |
| Computador da recepção | 1 | Cadastros e agendamentos |
| Computador do administrador | 1 | Gerenciamento de usuários e operações administrativas |
| Computadores ou notebooks dos psicólogos | conforme a equipe | Agenda e evoluções técnicas |
| Nobreak | 1 | Reduz o risco de perda de dados em quedas de energia |

## Topologia
A proposta usa a **topologia em estrela**: os equipamentos ficam ligados ao switch, e o switch fica ligado ao roteador.

Vantagens para uma clínica pequena: instalação e manutenção simples, e a falha de um computador não derruba os demais. Ponto de atenção: o switch e o roteador são pontos únicos de falha.

## Endereços IP (exemplos de planejamento)

| Rede | Faixa | Uso |
|---|---|---|
| Funcionários | 192.168.10.0/24 | Computadores da clínica |
| Visitantes | 192.168.20.0/24 | Wi-Fi para pacientes e responsáveis, isolado da rede interna |

Os endereços são **exemplos de planejamento**, não endereços reais. Na proposta, o **DHCP** do roteador distribuiria os IPs automaticamente.

## Protocolos de rede considerados na proposta

| Protocolo | Para que serviria |
|---|---|
| TCP/IP | Base da comunicação em rede |
| DHCP | Distribuição dos IPs dentro da clínica |
| DNS | Tradução de nomes em endereços IP |
| HTTPS/TLS | Somente se o sistema evoluir para cliente-servidor: protegeria os dados em trânsito |

Nenhum desses protocolos é usado pelo protótipo atual, que não se comunica por rede.
