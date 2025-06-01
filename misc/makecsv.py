import random
import csv
from datetime import datetime, timedelta

# Lista de nomes
NOMES = [
    "João", "Maria", "Carlos", "Ana", "Pedro", "Fernanda", "Lucas", "Juliana",
    "Rafael", "Beatriz", "Gabriel", "Larissa", "Mateus", "Camila", "Felipe",
    "Isabela", "Gustavo", "Amanda", "Bruno", "Letícia", "Thiago", "Natália",
    "Diego", "Vanessa", "André", "Patrícia", "Henrique", "Débora", "Vinícius",
    "Priscila", "Leonardo", "Adriana", "Rodrigo", "Renata", "Eduardo", "Cristina", "Thiago", "Heitor"
]

# Lista de sobrenomes
SOBRENOMES = [
    "Silva", "Santos", "Oliveira", "Souza", "Pereira", "Costa", "Rodrigues",
    "Almeida", "Nascimento", "Lima", "Araújo", "Fernandes", "Carvalho", "Gomes",
    "Martins", "Rocha", "Ribeiro", "Alves", "Monteiro", "Mendes", "Cardoso", "Peixoto",
    "Nunes", "Teixeira", "Barbosa", "Melo", "Campos", "Castro", "Pinto", "Lima",
    "Freitas", "Dias", "Machado", "Vieira", "Moreira", "Ramos", "Correia",
    "Andrade", "Ferreira", "Moura", "Cunha", "Batista", "Lopes", "Miranda", "Paixão"
]

def gerar_cpf():
    """Gera um CPF válido aleatório"""
    def calcular_digito(cpf_parcial):
        soma = sum(int(cpf_parcial[i]) * (len(cpf_parcial) + 1 - i) for i in range(len(cpf_parcial)))
        resto = soma % 11
        return 0 if resto < 2 else 11 - resto
    
    # Gera os 9 primeiros dígitos
    cpf = [random.randint(0, 9) for _ in range(9)]
    
    # Calcula os dígitos verificadores
    cpf.append(calcular_digito(cpf))
    cpf.append(calcular_digito(cpf))
    
    # Formata o CPF
    cpf_str = ''.join(map(str, cpf))
    return f"{cpf_str[:3]}.{cpf_str[3:6]}.{cpf_str[6:9]}-{cpf_str[9:]}"

def gerar_nome():
    """Gera um nome completo com 1 nome e 1-2 sobrenomes"""
    nome = random.choice(NOMES)
    num_sobrenomes = random.choice([1, 2])
    sobrenomes = random.sample(SOBRENOMES, num_sobrenomes)
    return f"{nome} {' '.join(sobrenomes)}"

def gerar_data():
    """Gera uma data aleatória entre 1970 e 2025"""
    inicio = datetime(1970, 1, 1)
    fim = datetime(2025, 12, 31)
    
    delta = fim - inicio
    dias_aleatorios = random.randint(0, delta.days)
    data_aleatoria = inicio + timedelta(days=dias_aleatorios)
    
    return data_aleatoria.strftime("%Y-%m-%d")

def gerar_linha(id_paciente):
    """Gera uma linha completa do CSV"""
    cpf = gerar_cpf()
    nome = gerar_nome()
    idade = random.randint(18, 90)
    data = gerar_data()
    
    return [id_paciente, cpf, nome, idade, data]

def gerar_csv(num_linhas, nome_arquivo="pacientes_gerados.csv"):
    """Gera um arquivo CSV com o número especificado de linhas"""
    with open(nome_arquivo, 'w', newline='', encoding='utf-8') as arquivo:
        writer = csv.writer(arquivo)
        
        for i in range(1, num_linhas + 1):
            linha = gerar_linha(i)
            writer.writerow(linha)
    
    print(f"Arquivo '{nome_arquivo}' gerado com {num_linhas} linhas!")

# Exemplo de uso
if __name__ == "__main__":
    # Gera 100 linhas por padrão
    num_linhas = int(input("Quantas linhas deseja gerar? (padrão: 100): ") or "100")
    nome_arquivo = input("Nome do arquivo (padrão: pacientes_gerados.csv): ") or "pacientes_gerados.csv"
    
    gerar_csv(num_linhas, nome_arquivo)
    
    # Exibe algumas linhas de exemplo
    print("\nPrimeiras 5 linhas geradas:")
    for i in range(1, 6):
        linha = gerar_linha(i)
        print(",".join(map(str, linha)))