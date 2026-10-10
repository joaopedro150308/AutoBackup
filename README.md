# Ideia do sistema

É um sistema que ferá backups de maneira automática. O usuário deve ser capaz de configuar quais pastas serão salvas e onde elas serão salvas. A configuração deve ser persistente, isto é, deve ficar salva no programa até que o usuário a mude.

# Requisitos

- O sistema deve ser um aplicativo executável, disponível ao acesso do usuário e deve ser possívelmente executado automáticamente pelo agendador de tarefas do windows.

- O sistema deve contar com uma pequena interface de navegação via cmd.

- Quanto aos arquivos que serão copiados, o programa deve ter algumas funções, tais como:
    - Selecionar arquivos
    - Remover arquivos
    - Mostrar arquivos selecionados

- Quanto para onde eles serão copiados, o usuário deve ter a opção:
    - Selecionar destino do backup

- Quanto aos backups, o usuário deve ter a opção de iniciá-los e, uma vez feito, todos os arquivos previamente listados para backup serão copiados para o destino também configurado. Se qualquer um desses dois requisitos não for atendido, não se pode fazer o backup.

    - Cada backup realizado pelo sistema ficará salvo em uma pasta padrão chamada Backups. Essa deve ser criada automaticamente, se não existir, no caminho configurado como destino. Sua existência também é pré-requisito para realizar um backup.

    - Para cada backup, será criado na pasta padrão (Backups) uma outra pasta que representará esse backup. Ela terá como nome a data de quando foi gerada. Seu conteúdo será a cópia de todos os arquivos previamente configurados.

# Abordagens para o desenvolvimento

    # Estrutura básica da pasta padrão Backups:

        Backups
            - dd/mm/aaaa (backup 1)
            - dd/mm/aaaa (backup 2)
                . . .
            - dd/mm/aaaa (backup n)
    
    