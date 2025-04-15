//Atividade 1 AED1 2024 Prof Luis
//Lucas de Oliveira Kwok 163919

#include <stdio.h>

int contaLetras(char str[500]){

    int l= 0,d = 0,c = 0;

    for(int cont=0;cont<500;cont++){
        if(str[cont] == '\0') 
            break;
        if((str[cont] >= 'a' && str[cont] <= 'z') || (str[cont] >= 'A' && str[cont] <= 'Z'))
            l++;
        else if(str[cont] >= '0' && str[cont] <= '9')
            d++;
        else c++;
    }
    return (l - d) * c;
}

int comparaString(char str1[500], char str2[500]){
    int cont = 0;
    for(cont;cont<500;cont++){
        if(str1[cont] == '\0') 
            break;
        if(str1[cont] != str2[cont])
            return 0;
    }

    if(str1[cont] == '\0' && str2[cont] == '\0') 
        return 1;
    else 
        return 0;
}

int main()
{
    char str1[500], str2[500];

    scanf("%s", str1);
    scanf("%s", str2);

    printf("%d %d %d", contaLetras(str1), contaLetras(str2), comparaString(str1, str2));

    return 0;
}
