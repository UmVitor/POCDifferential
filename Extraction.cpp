#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
float AmplificadorInstrumentacaoModelo(float Vin1, float Vin2);
void LimpaArquivoMixerLtSpice();

int main() 
{ 
  LimpaArquivoMixerLtSpice(); 
}

void LimpaArquivoMixerLtSpice() {
  string filename = "Signals.csv";
  ifstream file(filename);
  string line;
  vector<double> time, v1, v2;
  double t, v1_val, v2_val;
  string output_filename = "saida.txt";
  ofstream output_file(output_filename);

  if (file.is_open()) {
    getline(file, line);
    while (getline(file, line)) {
      istringstream ss(line);
      ss >> t >> v1_val >> v2_val;
      time.push_back(t);
      v1.push_back(v1_val);
      v2.push_back(v2_val);
    }
    file.close();
  } else {
    cout << "Erro ao abrir o arquivo " << filename << endl;
  }

  for (int i = 0; i < time.size(); i++) {
    output_file << time[i] << " "
                << AmplificadorInstrumentacaoModelo(v1[i], v2[i]) << endl;
  }
}

float AmplificadorInstrumentacaoModelo(float Vin1, float Vin2) {
  float R1 = 10e3;
  float R2 = 10e3;
  float R3 = 10e3;
  float R4 = 10e3;
  float Vout;
  float ganho = (R4 / R3) * (1 + (R2 / R1));
  Vout = ganho * (Vin2 - Vin1);
  return Vout;
}
