import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
import random

PARAMETROS_IDEAIS = {
    "Cactos": {"temperatura": (20, 35), "luminosidade": (70, 100), "umidade": (800, 1000)},
    "Orquídea": {"temperatura": (18, 25), "luminosidade": (40, 70), "umidade": (800, 1000)},
}

def gerar_dados_fake():
    tipos_plantas = ["Cactos", "Orquídea"]
    dados = []
    for _ in range(100):
        tipo = random.choice(tipos_plantas)
        temp = random.uniform(10, 40)
        lumi = random.uniform(30, 110)
        umid = random.uniform(700, 1100)
        estado = "saudável" if (
            PARAMETROS_IDEAIS[tipo]["temperatura"][0] <= temp <= PARAMETROS_IDEAIS[tipo]["temperatura"][1]
            and PARAMETROS_IDEAIS[tipo]["luminosidade"][0] <= lumi <= PARAMETROS_IDEAIS[tipo]["luminosidade"][1]
            and PARAMETROS_IDEAIS[tipo]["umidade"][0] <= umid <= PARAMETROS_IDEAIS[tipo]["umidade"][1]
        ) else "problema"
        dados.append({"tipo": tipo, "temperatura": temp, "luminosidade": lumi, "umidade": umid, "estado": estado})
    return pd.DataFrame(dados)

dados_historicos = gerar_dados_fake()

X = dados_historicos[["temperatura", "luminosidade", "umidade"]]
y = dados_historicos["estado"]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

modelo = RandomForestClassifier(random_state=42)
modelo.fit(X_train, y_train)

precisao = modelo.score(X_test, y_test)
print(f"Precisão do modelo: {precisao * 100:.2f}%")

def gerar_recomendacoes(novos_dados, tipo_planta):
    predicao = modelo.predict([list(novos_dados.values())])[0]
    if predicao == "saudável":
        return {"mensagem": "Sua planta está saudável! Continue assim."}
    
    recomendacoes = []
    parametros = PARAMETROS_IDEAIS[tipo_planta]
    if novos_dados["temperatura"] < parametros["temperatura"][0]:
        recomendacoes.append("Aumentar a temperatura.")
    elif novos_dados["temperatura"] > parametros["temperatura"][1]:
        recomendacoes.append("Reduzir a temperatura.")
    if novos_dados["luminosidade"] < parametros["luminosidade"][0]:
        recomendacoes.append("Aumentar a exposição à luz.")
    elif novos_dados["luminosidade"] > parametros["luminosidade"][1]:
        recomendacoes.append("Reduzir a exposição à luz.")
    if novos_dados["umidade"] < parametros["umidade"][0]:
        recomendacoes.append("Aumentar a rega.")
    elif novos_dados["umidade"] > parametros["umidade"][1]:
        recomendacoes.append("Reduzir a frequência de rega.")
    
    return {"mensagem": "Sua planta está com problemas.", "recomendacoes": recomendacoes}

# Entrada manual para simular novos dados
print("\nDigite os valores atuais da planta:")
temperatura = float(input("Temperatura (°C): "))
luminosidade = float(input("Luminosidade (%): "))
umidade = float(input("Umidade: "))
tipo_planta = input("Tipo de planta (Cactos ou Orquídea): ")

novo_dado = {"temperatura": temperatura, "luminosidade": luminosidade, "umidade": umidade}
resultado = gerar_recomendacoes(novo_dado, tipo_planta)

print("\nResultados da análise:")
print(resultado)

