global idtLoad
idtLoad:
    lidt [eax]
    ret
