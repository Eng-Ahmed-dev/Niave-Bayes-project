#include <iostream>
using namespace std;
class Weather {
public:
	/// <summary>
	/// when outlook = 0 its sunny; outlook 1 overcast; outlook 2 rain;
	/// when temperature =0 cool; =1 mild; =2 hot;
	/// when humidity =0 normal; =1 high;
	/// when wind = 0 weak; =1 strong; 
	/// when play =0 thats mean no;otherwise yes;
	/// </summary>
	int outlook;
	int temperature;
	int humidity;
	int wind;
	int play;
	Weather(int a, int b, int c, int d, int f) {
		outlook = a;
		temperature = b;
		humidity = c;
		wind = d;
		play = f;
	}

	Weather(int a, int b, int c, int d) {
		outlook = a;
		temperature = b;
		humidity = c;
		wind = d;
		play = 0;
	}

};


Weather arr[] = {
	Weather(0, 2, 1, 0, 0),
	Weather(0, 2, 1, 1, 0),
	Weather(1, 2, 1, 0, 1),
	Weather(2, 1, 1, 0, 1),
	Weather(2, 0, 0, 0, 1),
	Weather(2, 0, 0, 1, 0),
	Weather(1, 0, 0, 1, 1),
	Weather(0, 1, 1, 0, 0),
	Weather(0, 0, 0, 0, 1),
	Weather(2, 1, 0, 0, 1),
	Weather(0, 1, 0, 1, 1),
	Weather(1, 1, 1, 1, 1),
	Weather(1, 2, 0, 0, 1),
	Weather(2, 1, 1, 1, 0)
};
bool checkPlay(Weather a) {
    int playCount = 0;
    int noPlayCount = 0;

    // Count total play and no-play cases
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        if (arr[i].play) playCount++;
        else noPlayCount++;
    }

    // Calculate prior probabilities
    float total = playCount + noPlayCount;
    float pPlay = playCount / total;
    float pNoPlay = noPlayCount / total;

    // Calculate conditional probabilities for each feature
    float pOutlookPlay = 0, pTempPlay = 0, pHumidityPlay = 0, pWindPlay = 0;
    float pOutlookNoPlay = 0, pTempNoPlay = 0, pHumidityNoPlay = 0, pWindNoPlay = 0;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        if (arr[i].play) {
            if (arr[i].outlook == a.outlook) pOutlookPlay++;
            if (arr[i].temperature == a.temperature) pTempPlay++;
            if (arr[i].humidity == a.humidity) pHumidityPlay++;
            if (arr[i].wind == a.wind) pWindPlay++;
        }
        else {
            if (arr[i].outlook == a.outlook) pOutlookNoPlay++;
            if (arr[i].temperature == a.temperature) pTempNoPlay++;
            if (arr[i].humidity == a.humidity) pHumidityNoPlay++;
            if (arr[i].wind == a.wind) pWindNoPlay++;
        }
    }

    // Normalize probabilities 
    pOutlookPlay /= playCount;
    pTempPlay /= playCount;
    pHumidityPlay /= playCount;
    pWindPlay /= playCount;

    pOutlookNoPlay /= noPlayCount;
    pTempNoPlay /= noPlayCount;
    pHumidityNoPlay /= noPlayCount;
    pWindNoPlay /= noPlayCount;

    // Calculate final probabilities
    float playProbability = pPlay * pOutlookPlay * pTempPlay * pHumidityPlay * pWindPlay;
    float noPlayProbability = pNoPlay * pOutlookNoPlay * pTempNoPlay * pHumidityNoPlay * pWindNoPlay;

    return playProbability > noPlayProbability;
}

int main(){
		
	Weather sundayNight(0, 0, 0, 0);
	if (checkPlay(sundayNight)) {
		cout << "\nlets Gooo Baby";
    }
    else
        cout << "\n NO PLAY!!";
}
/// <summary>
    /// when outlook = 0 its sunny; outlook 1 overcast; outlook 2 rain;
    /// when temperature =0 cool; =1 mild; =2 hot;
    /// when humidity =0 normal; =1 high;
    /// when wind = 0 weak; =1 strong; 
    /// when play =0 thats mean no;otherwise yes;
    /// </summary>

/*
#include <iostream>
#include <vector>
#include <cmath>  // For log and exp functions
using namespace std;

class Weather {
public:
    int outlook;      // 0 = Sunny, 1 = Overcast, 2 = Rain
    int temperature;  // 0 = Cool, 1 = Mild, 2 = Hot
    int humidity;     // 0 = Normal, 1 = High
    int wind;         // 0 = Weak, 1 = Strong
    int play;         // 0 = No, 1 = Yes

    Weather(int a, int b, int c, int d, int f) {
        outlook = a;
        temperature = b;
        humidity = c;
        wind = d;
        play = f;
    }

    Weather(int a, int b, int c, int d) {
        outlook = a;
        temperature = b;
        humidity = c;
        wind = d;
        play = 0;
    }
};

// Training data (arr of Weather objects)
Weather arr[] = {
    Weather(0, 2, 1, 0, 0), Weather(0, 2, 1, 1, 0), Weather(1, 2, 1, 0, 1),
    Weather(2, 1, 1, 0, 1), Weather(2, 0, 0, 0, 1), Weather(2, 0, 0, 1, 0),
    Weather(1, 0, 0, 1, 1), Weather(0, 1, 1, 0, 0), Weather(0, 0, 0, 0, 1),
    Weather(2, 1, 0, 0, 1), Weather(0, 1, 0, 1, 1), Weather(1, 1, 1, 1, 1),
    Weather(1, 2, 0, 0, 1), Weather(2, 1, 1, 1, 0)
};

// Function to calculate probabilities for Naive Bayes
bool checkPlay(Weather a) {
    // Count of instances where play = 1 (Yes) and play = 0 (No)
    int play_yes = 0, play_no = 0;

    // Count occurrences of feature values for Play = Yes (1) and Play = No (0)
    int feature_counts_yes[4][3] = {};  // 4 features, 3 possible values per feature
    int feature_counts_no[4][3] = {};

   
    for eac (const auto& w : arr) {
        if (w.play == 1) {
            play_yes++;
            feature_counts_yes[0][w.outlook]++;
            feature_counts_yes[1][w.temperature]++;
            feature_counts_yes[2][w.humidity]++;
            feature_counts_yes[3][w.wind]++;
        }
        else {
            play_no++;
            feature_counts_no[0][w.outlook]++;
            feature_counts_no[1][w.temperature]++;
            feature_counts_no[2][w.humidity]++;
            feature_counts_no[3][w.wind]++;
        }
    }

    // Calculate probabilities for Play = Yes and Play = No using Laplace smoothing
    double prob_yes = (double)play_yes / (play_yes + play_no);
    double prob_no = (double)play_no / (play_yes + play_no);

    // Calculate the likelihood for each feature and class
    double prob_features_given_yes = log(prob_yes);
    double prob_features_given_no = log(prob_no);

    // Feature probabilities for Play = Yes
    prob_features_given_yes += log((feature_counts_yes[0][a.outlook] + 1.0) / (play_yes + 3));  // Laplace smoothing
    prob_features_given_yes += log((feature_counts_yes[1][a.temperature] + 1.0) / (play_yes + 3));
    prob_features_given_yes += log((feature_counts_yes[2][a.humidity] + 1.0) / (play_yes + 2));
    prob_features_given_yes += log((feature_counts_yes[3][a.wind] + 1.0) / (play_yes + 2));

    // Feature probabilities for Play = No
    prob_features_given_no += log((feature_counts_no[0][a.outlook] + 1.0) / (play_no + 3));
    prob_features_given_no += log((feature_counts_no[1][a.temperature] + 1.0) / (play_no + 3));
    prob_features_given_no += log((feature_counts_no[2][a.humidity] + 1.0) / (play_no + 2));
    prob_features_given_no += log((feature_counts_no[3][a.wind] + 1.0) / (play_no + 2));

    // Compare the probabilities for Play = Yes vs Play = No
    return prob_features_given_yes > prob_features_given_no;
}

int main() {
    // New test data for prediction (e.g., Sunny, Hot, High, Strong wind)
    Weather sundayNight(2, 2, 1, 1);

    // Check if we should play or not
    if (checkPlay(sundayNight)) {
        cout << "\nLet's Gooo Baby!" << endl;
    }
    else {
        cout << "\nNo Play, Sorry!" << endl;
    }

    return 0;
}
*/
