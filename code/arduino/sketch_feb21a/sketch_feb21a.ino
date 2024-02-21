
#include <math.h> // For the exp function in sigmoid
#include <Arduino_LSM9DS1.h>

#define INPUT_NODES 1
#define HIDDEN_NODES1 5
#define HIDDEN_NODES2 6
#define OUTPUT_NODES 1

float weights_layer_0[1][5] = {{-0.940025, 0.380151, 0.5200327, 0.4343022, 0.78406924}};

float bias_layer_0[] = {0.8342049717903137, -0.27528828382492065, -1.0074617862701416, -0.20403210818767548, -0.36128801107406616};

float weights_layer_1[5][5] = {{-0.11460345, -0.64200896, 0.08240323, 0.838257, 0.959287},
{0.14622043, 0.3735112, 0.08595258, 0.9383323, 0.24393703},
{-0.056797776, -0.47232583, 0.1831359, 1.1638113, 0.7995385},
{0.012193634, -0.62377703, 0.42523837, 0.20095773, 0.6390538},
{0.81144977, -0.5480915, 0.11595223, -0.55135876, 0.06384433}};

float bias_layer_1[] = {-0.019182732328772545, 0.03272715583443642, -0.05897887796163559, 0.2689266502857208, 0.11577402055263519};

float weights_layer_2[5][1] = {{0.8319306},
{0.007486782},
{-0.39753956},
{-1.0058185},
{-0.6842462}};

float bias_layer_2[] = {0.055825281888246536};


// Assuming these weights and biases are already trained
#define weights_input_hidden1 weights_layer_0
#define weights_hidden1_hidden2 weights_layer_1
#define weights_hidden2_output weights_layer_2

float bias_hidden1[HIDDEN_NODES1] = {/* biases for first hidden layer */};
float bias_hidden2[HIDDEN_NODES2] = {/* biases for second hidden layer */};
float bias_output[OUTPUT_NODES] = {/* biases for output layer */};

float relu(float x) {
    return x > 0 ? x : 0;
}

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}


void forward(float input, float output[OUTPUT_NODES]) {
    float hidden1[HIDDEN_NODES1] = {0};
    float hidden2[HIDDEN_NODES2] = {0};
    
    // Input to Hidden Layer 1
    for(int i = 0; i < HIDDEN_NODES1; i++) {
        hidden1[i] = input * weights_input_hidden1[0][i] + bias_hidden1[i];
        hidden1[i] = relu(hidden1[i]);
    }
    
    // Hidden Layer 1 to Hidden Layer 2
    for(int i = 0; i < HIDDEN_NODES2; i++) {
        for(int j = 0; j < HIDDEN_NODES1; j++) {
            hidden2[i] += hidden1[j] * weights_hidden1_hidden2[j][i];
        }
        hidden2[i] += bias_hidden2[i];
        hidden2[i] = relu(hidden2[i]);
    }
    
    // Hidden Layer 2 to Output
    for(int i = 0; i < OUTPUT_NODES; i++) {
        for(int j = 0; j < HIDDEN_NODES2; j++) {
            output[i] += hidden2[j] * weights_hidden2_output[j][i];
        }
        output[i] += bias_output[i];
        output[i] = relu(output[i]);
    }
}


void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");

}

void loop() {
  // read sensorda
  float sensor_wert = 0.4f ;
  //
  float output[OUTPUT_NODES];

  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);

    forward(x, output);
    Serial.print('SIN ');
    Serial.println(output[0]);

  }
    
  


}
