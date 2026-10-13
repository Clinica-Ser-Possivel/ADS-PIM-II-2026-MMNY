# Estrutura da Rede

## Como é a clínica
É uma clínica pequena, com uma única unidade e sem filiais. Por isso a rede foi pensada para ser simples, segura e fácil de manter.

## Equipamentos

| Equipamento | Quantidade | Para que serve |
|---|---|---|
| Roteador com firewall | 1 | Liga a clínica à internet e bloqueia acessos indevidos |
| Switch | 1 | Conecta os computadores da rede cabeada |
| Access point (Wi-Fi) | 1 | Dá Wi-Fi para os funcionários e outro Wi-Fi separado para visitantes |
| Computador da recepção | 1 | Cadastro, agendamento e cancelamento |
| Computador do assistente administrativo | 1 | Cobrança e rotinas administrativas |
| Computadores ou notebooks dos psicólogos | conforme a equipe | Prontuário e evolução das sessões |
| Computador do psicólogo RT | 1 | Supervisão, com o acesso que for permitido |
| Impressora | 1 | Documentos e laudos |
| Nobreak | 1 | Evita perda de dados quando a energia cai |

## Topologia
A rede usa a **topologia em estrela**: todos os equipamentos ficam ligados ao switch, e o switch fica ligado ao roteador.

## Endereços IP

| Rede | Faixa | Uso |
|---|---|---|
| Funcionários | 192.168.10.0/24 | Computadores da clínica |
| Visitantes | 192.168.20.0/24 | Wi-Fi para pacientes e responsáveis, sem acesso ao sistema interno |

- O **DHCP** do roteador entrega os IPs automaticamente.
- A impressora usa um **IP fixo** (por exemplo, 192.168.10.50).

## Protocolos usados

| Protocolo | Para que serve no projeto |
|---|---|
| TCP/IP | É a base da comunicação na rede |
| HTTP/HTTPS (porta 443) | Acesso ao sistema pelo navegador, com os dados protegidos |
| DNS | Transforma o endereço do sistema em um IP |
| DHCP | Distribui os IPs dentro da clínica |
| SMTP | Envia os e-mails de lembrete das sessões |
| TLS | Criptografa os dados enquanto eles trafegam |
