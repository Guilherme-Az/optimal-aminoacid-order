#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Obter os índices de cada classe
int obterClasse(char c){
    switch(c){
        case 'P': return 0;
        case 'N': return 1;
        case 'A': return 2;
        case 'B': return 3;
        case 'T': return 4;
        default: return 4; // Terminal por padrão
    }
}

/* Calcula a energia libertada ao remover aminoácido k */
unsigned long long calcularEnergia(unsigned long long P_left,
                                   unsigned long long P_k,
                                   unsigned long long P_right,
                                   int C_left, int C_k, int C_right,
                                   const int af[5][5]){
    return 1ULL * P_left * af[C_left][C_k] * P_k
         + 1ULL * P_k    * af[C_k][C_right] * P_right;
}
    
// Reconstrói a sequência ótima do intervalo [i,j]
void constroiSeq(int i, int j, const vector<vector<int>> &parent, vector<int> &seq){
    if(i>j) return;
    int k = parent[i][j];
    if(k==-1) return;
    constroiSeq(i, k-1, parent, seq);
    constroiSeq(k+1, j, parent, seq);
    seq.push_back(k);
}

// Compara duas sequências lexicograficamente
bool compararSequencias(const vector<int> &a, const vector<int> &b) {
    int na = a.size(); 
    int nb = b.size();
    int mn = min(na, nb);
    for(int i=0; i<mn; i++){
        if(a[i]!=b[i]) return a[i] < b[i];
    }
    return na < nb;
}

void obterMatrizes(vector<vector<unsigned long long>> &energias,
                   vector<vector<vector<int>>> &ordem_unused,
                   const vector<unsigned long long> &P,
                   const vector<int> &C,
                   const int af[5][5],
                   int n){

    vector<vector<int>> parent(n+2, vector<int>(n+2, -1));

    // Inicializar energias com um valor muito pequeno (0, pois ULL não permite negativos)
    for(int i=0; i<=n+1; i++)
        for(int j=0; j<=n+1; j++)
            energias[i][j] = 0;

    // DP por comprimento
    for(int len=1; len<=n; len++){
        for(int i=1; i<=n-len+1; i++){
            int j = i+len-1;

            unsigned long long melhor = 0;
            int melhor_k = -1;

            for(int k=i; k<=j; k++){
                unsigned long long energia_k = calcularEnergia(P[i-1], P[k], P[j+1],
                                                                C[i-1], C[k], C[j+1], af);
                unsigned long long esquerda = (k > i ? energias[i][k-1] : 0);
                unsigned long long direita  = (k < j ? energias[k+1][j] : 0);

                unsigned long long total = esquerda + direita + energia_k;

                if(total > melhor){
                    melhor = total;
                    melhor_k = k;
                }
                else if(total == melhor){
                    // desempate lexicográfico
                    vector<int> atual;
                    if(melhor_k != -1) constroiSeq(i, j, parent, atual);

                    vector<int> proposto;
                    if(k > i) constroiSeq(i, k-1, parent, proposto);
                    if(k < j) constroiSeq(k+1, j, parent, proposto);
                    proposto.push_back(k);

                    if(atual.empty() || compararSequencias(proposto, atual)){
                        melhor_k = k;
                    }
                }
            }

            energias[i][j] = melhor;
            parent[i][j] = melhor_k;
        }
    }

    // Guardar apenas a ordem de [1][n]
    for(int i=0; i<=n+1; i++)
        for(int j=0;j<=n+1;j++)
            ordem_unused[i][j].clear();

    vector<int> final_seq;
    constroiSeq(1, n, parent, final_seq);
    ordem_unused[1][n] = final_seq;
}

int main(){
    int n;
    cin >> n;

    vector<unsigned long long> P(n+2, 1);
    vector<int> C(n+2, 4);

    for(int i=1; i<=n; i++)
        cin >> P[i];

    for(int i=1; i<=n; i++){
        char classe;
        cin >> classe;
        C[i] = obterClasse(classe);
    }

    vector<vector<unsigned long long>> energias(n+2, vector<unsigned long long>(n+2));
    vector<vector<vector<int>>> ordem(n+2, vector<vector<int>>(n+2));

    int af[5][5] = {
        {1, 3, 1, 3, 1},
        {5, 1, 0, 1, 1},
        {0, 1, 0, 4, 1},
        {1, 3, 2, 3, 1},
        {1, 1, 1, 1, 1}
    };

    obterMatrizes(energias, ordem, P, C, af, n);

    cout << energias[1][n] << "\n";

    for(size_t i=0;i<ordem[1][n].size();i++){
        if(i) cout << " ";
        cout << ordem[1][n][i];
    }
    cout << "\n";

    return 0;
}
