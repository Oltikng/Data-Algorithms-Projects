#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Arrival {
    int id;
    char type;
};

void parseInput(const string& file_name, int& P_Officers, int& N_Officers, int& P_Time, int& N_Time, vector<int>& P_Control, vector<int>& N_Control, vector<Arrival>& arrivals) {
    ifstream file(file_name);

    file >> P_Officers >> N_Officers >> P_Time >> N_Time;

    char Type;
    int Officer, Time;
    for (int i = 0; i < P_Officers; ++i) {
        file >> Type >> Officer >> Time;
        P_Control.push_back(Time);
    }

    for (int i = 0; i < N_Officers; ++i) {
        file >> Type >> Officer >> Time;
        N_Control.push_back(Time);
    }

    Arrival arr;
    while (file >> arr.type >> arr.id) {
        arrivals.push_back(arr);
    }

    file.close();
}

int main() {
    int P_Officers, N_Officers, P_Time, N_Time;
    vector<int> P_Control, N_Control;
    vector<Arrival> arrivals;

    parseInput("customs.in", P_Officers, N_Officers, P_Time, N_Time, P_Control, N_Control, arrivals);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> P_Customs, N_Customs;

    for (int i = 0; i < P_Officers; ++i) {
        P_Customs.push({0, i});
    }

    for (int i = 0; i < N_Officers; ++i) {
        N_Customs.push({0, i});
    }

    ofstream output("customs.out");

    for (const auto& arrival : arrivals) {
        int exit_time;
        if (arrival.type == 'P') {
            auto [time, officer_id] = P_Customs.top();
            P_Customs.pop();
            exit_time = max(time, arrival.id) + P_Time;
            P_Customs.push({exit_time, officer_id});
        } else {
            auto [time, officer_id] = N_Customs.top();
            N_Customs.pop();
            exit_time = max(time, arrival.id) + N_Time;
            N_Customs.push({exit_time, officer_id});
        }
        output << exit_time << "\n";
    }

    output.close();

    return 0;
}