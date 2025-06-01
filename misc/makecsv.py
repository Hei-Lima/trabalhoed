import random
import csv
from datetime import datetime, timedelta
import itertools

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

# Nomes especiais obrigatórios
NOMES_ESPECIAIS = [
    {"nome": "Gian Lucca Decote Paneto", "cpf": "000.000.000-000"},
    {"nome": "Thiago Paixão", "cpf": "PR0.FES.SS0-R0"},
    {"nome": "Heitor Lima Peixoto", "cpf": "999.999.999-99"}
]

def gerar_todas_permutacoes_nomes():
    """Gera todas as combinações possíveis de nomes com 1-2 sobrenomes"""
    permutacoes = []
    
    # Combinações com 1 sobrenome
    for nome in NOMES:
        for sobrenome in SOBRENOMES:
            permutacoes.append(f"{nome} {sobrenome}")
    
    # Combinações com 2 sobrenomes
    for nome in NOMES:
        for sobrenome1, sobrenome2 in itertools.combinations(SOBRENOMES, 2):
            permutacoes.append(f"{nome} {sobrenome1} {sobrenome2}")
    
    # Remove os nomes especiais se já existirem na lista
    nomes_especiais_str = [item["nome"] for item in NOMES_ESPECIAIS]
    permutacoes = [nome for nome in permutacoes if nome not in nomes_especiais_str]
    
    return permutacoes

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

def gerar_data():
    """Gera uma data aleatória entre 1970 e 2025"""
    inicio = datetime(1970, 1, 1)
    fim = datetime(2025, 12, 31)
    
    delta = fim - inicio
    dias_aleatorios = random.randint(0, delta.days)
    data_aleatoria = inicio + timedelta(days=dias_aleatorios)
    
    return data_aleatoria.strftime("%Y-%m-%d")

def gerar_linha(id_paciente, nome, cpf=None):
    """Gera uma linha completa do CSV com nome específico"""
    if cpf is None:
        cpf = gerar_cpf()
    idade = random.randint(18, 90)
    data = gerar_data()
    
    return [id_paciente, cpf, nome, idade, data]

def gerar_csv(num_linhas, nome_arquivo="pacientes_gerados.csv"):
    """Gera um arquivo CSV com o número especificado de linhas"""
    # Gera todas as permutações possíveis
    nomes_unicos = gerar_todas_permutacoes_nomes()
    
    # Embaralha a lista para ordem aleatória
    random.shuffle(nomes_unicos)
    
    # Calcula quantas permutações temos (incluindo os nomes especiais)
    total_permutacoes = len(nomes_unicos) + len(NOMES_ESPECIAIS)
    
    print(f"Total de permutações únicas possíveis: {total_permutacoes}")
    
    if num_linhas > total_permutacoes:
        print(f"AVISO: Solicitadas {num_linhas} linhas, mas só existem {total_permutacoes} permutações únicas.")
        print(f"Gerando {total_permutacoes} linhas com nomes únicos.")
        num_linhas = total_permutacoes
    
    with open(nome_arquivo, 'w', newline='', encoding='utf-8') as arquivo:
        writer = csv.writer(arquivo)
        
        # Primeiro, escreve os nomes especiais
        for i, especial in enumerate(NOMES_ESPECIAIS):
            linha = gerar_linha(i + 1, especial["nome"], especial["cpf"])
            writer.writerow(linha)
        
        # Depois, escreve os nomes restantes
        nomes_restantes = num_linhas - len(NOMES_ESPECIAIS)
        for i in range(nomes_restantes):
            if i < len(nomes_unicos):
                nome = nomes_unicos[i]
                linha = gerar_linha(len(NOMES_ESPECIAIS) + i + 1, nome)
                writer.writerow(linha)
    
    print(f"Arquivo '{nome_arquivo}' gerado com {num_linhas} linhas!")
    print(f"Incluindo {len(NOMES_ESPECIAIS)} nomes especiais obrigatórios.")

# Exemplo de uso
if __name__ == "__main__":
    # Calcula o máximo de permutações possíveis
    total_max = len(NOMES) * len(SOBRENOMES) + len(NOMES) * len(SOBRENOMES) * (len(SOBRENOMES) - 1) // 2 + len(NOMES_ESPECIAIS)
    
    print(f"Máximo de nomes únicos possíveis: {total_max}")
    print("Nomes especiais que sempre serão incluídos:")
    for especial in NOMES_ESPECIAIS:
        print(f"  - {especial['nome']} (CPF: {especial['cpf']})")
    print()
    
    # Gera 100 linhas por padrão
    num_linhas = int(input(f"Quantas linhas deseja gerar? (padrão: 100, máx: {total_max}): ") or "100")
    nome_arquivo = input("Nome do arquivo (padrão: pacientes_gerados.csv): ") or "pacientes_gerados.csv"
    
    gerar_csv(num_linhas, nome_arquivo)
    
    # Exibe algumas linhas de exemplo
    print("\nPrimeiras 5 linhas geradas:")
    with open(nome_arquivo, 'r', encoding='utf-8') as arquivo:
        reader = csv.reader(arquivo)
        for i, linha in enumerate(reader):
            if i < 5:
                print(",".join(linha))
            else:
                break