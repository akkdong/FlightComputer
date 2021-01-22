/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "main_functions.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "constants.h"
#include "model.h"
#include "output_handler.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "stm32h7xx_hal.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

#if 0
constexpr int kTensorArenaSize = 2000;
uint8_t tensor_arena[kTensorArenaSize];
#else
constexpr int kTensorArenaSize = 0x1000000;
uint8_t* tensor_arena = (uint8_t *)0xD0000000;
#endif
}  // namespace

// The name of this function is important for Arduino compatibility.
void tensorflow_setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;
}

// The name of this function is important for Arduino compatibility.
void tensorflow_loop() {
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x = position * kXrange;

  // Quantize the input from floating-point to integer
  int8_t x_quantized = x / input->params.scale + input->params.zero_point;
  // Place the quantized input in the model's input tensor
  input->data.int8[0] = x_quantized;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                         static_cast<double>(x));
    return;
  }

  // Obtain the quantized output from model's output tensor
  int8_t y_quantized = output->data.int8[0];
  // Dequantize the output from integer to floating-point
  float y = (y_quantized - output->params.zero_point) * output->params.scale;

  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.
  HandleOutput(error_reporter, x, y);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;
}



extern "C" void tensorflow_test1(void)
{
	// Set up logging. Google style is to avoid globals or statics because of
	// lifetime uncertainty, but since this has a trivial destructor it's okay.
	// NOLINTNEXTLINE(runtime-global-variables)
	static tflite::MicroErrorReporter micro_error_reporter;
	error_reporter = &micro_error_reporter;

	// Map the model into a usable data structure. This doesn't involve any
	// copying or parsing, it's a very lightweight operation.
	model = tflite::GetModel(g_model);
	if (model->version() != TFLITE_SCHEMA_VERSION) {
		TF_LITE_REPORT_ERROR(error_reporter,
							 "Model provided is schema version %d not equal "
							 "to supported version %d.",
							 model->version(), TFLITE_SCHEMA_VERSION);
		return;
	}

	// This pulls in all the operation implementations we need.
	// NOLINTNEXTLINE(runtime-global-variables)
	static tflite::AllOpsResolver resolver;

	// Build an interpreter to run the model with.
	static tflite::MicroInterpreter static_interpreter(
	  model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
	interpreter = &static_interpreter;

	// Allocate memory from the tensor_arena for the model's tensors.
	TfLiteStatus allocate_status = interpreter->AllocateTensors();
	if (allocate_status != kTfLiteOk) {
		TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
		return;
	}

	// Obtain pointers to the model's input and output tensors.
	input = interpreter->input(0);
	if (!input) {
		printf("ERR: no input\n");
		return;
	}

	printf("input.dims.size = %d\n", input->dims->size);
	HAL_Delay(10);
	printf(" dims.x = %d\n", input->dims->data[0]);
	HAL_Delay(10);
	printf(" dims.y = %d\n", input->dims->data[0]);
	HAL_Delay(10);
	printf("input.type = %d\n", input->type);
	HAL_Delay(10);

	// Get the input quantization parameters
	float input_scale = input->params.scale;
	int input_zero_point = input->params.zero_point;
	printf("input scale(%f), zero_point(%d)\n", input_scale, input_zero_point);
	HAL_Delay(10);


	float x = 1.0472; // 60 deg
	float y_true = sin(x); // 0.8660254

	int8_t x_quantized = x / input_scale * input_zero_point;
	input->data.int8[0] = x_quantized;


	output = interpreter->output(0);
	if (!input) {
		printf("ERR: no output\n");
		return;
	}

	// Run the model and check that it succeeds
	TfLiteStatus invoke_status = interpreter->Invoke();
	if (invoke_status != kTfLiteOk) {
		printf("ERR: interpreter.Invoke() --> %d\n", invoke_status);
		return;
	}

	printf("output.dims.size = %d\n", output->dims->size);
	HAL_Delay(10);
	printf(" dims.x = %d\n", output->dims->data[0]);
	HAL_Delay(10);
	printf(" dims.y = %d\n", output->dims->data[0]);
	HAL_Delay(10);
	printf("output.type = %d\n", output->type);
	HAL_Delay(10);


	// Get the output quantization parameters
	float output_scale = output->params.scale;
	int output_zero_point = output->params.zero_point;
	printf("output scale(%f), zero_point(%d)\n", output_scale, output_zero_point);
	HAL_Delay(10);


	// Obtain the quantized output from model's output tensor
	int8_t y_pred_quantized = output->data.int8[0];
	// Dequantize the output from integer to floating-point
	float y_pred = (y_pred_quantized - output_zero_point) * output_scale;

	printf("x = %f\n", x);
	printf("y_true = %f\n", y_true);
	printf("y_pred = %f\n", y_pred);
	printf(" --> diff: %f\n", y_true - y_pred);
	HAL_Delay(10);


	//
	x = 0.4;
	y_true = sin(x);

	x_quantized = x / input_scale * input_zero_point;
	input->data.int8[0] = x_quantized;

	invoke_status = interpreter->Invoke();
	if (invoke_status != kTfLiteOk) {
		printf("ERR: interpreter.Invoke(%f) --> %d\n", x, invoke_status);
		return;
	}

	y_pred_quantized = output->data.int8[0];
	y_pred = (y_pred_quantized - output_zero_point) * output_scale;

	printf("x = %f\n", x);
	printf("y_true = %f\n", y_true);
	printf("y_pred = %f\n", y_pred);
	printf(" --> diff: %f\n", y_true - y_pred);
	HAL_Delay(10);


	//
	x = 1.4;
	y_true = sin(x);

	x_quantized = x / input_scale * input_zero_point;
	input->data.int8[0] = x_quantized;

	invoke_status = interpreter->Invoke();
	if (invoke_status != kTfLiteOk) {
		printf("ERR: interpreter.Invoke(%f) --> %d\n", x, invoke_status);
		return;
	}

	y_pred_quantized = output->data.int8[0];
	y_pred = (y_pred_quantized - output_zero_point) * output_scale;

	printf("x = %f\n", x);
	printf("y_true = %f\n", y_true);
	printf("y_pred = %f\n", y_pred);
	printf(" --> diff: %f\n", y_true - y_pred);
	HAL_Delay(10);
}


extern "C" void tensorflow_test2(uint8_t* addrModel)
{
	// Set up logging. Google style is to avoid globals or statics because of
	// lifetime uncertainty, but since this has a trivial destructor it's okay.
	// NOLINTNEXTLINE(runtime-global-variables)
	static tflite::MicroErrorReporter micro_error_reporter;
	error_reporter = &micro_error_reporter;

	// Map the model into a usable data structure. This doesn't involve any
	// copying or parsing, it's a very lightweight operation.
	model = tflite::GetModel(addrModel);
	if (model->version() != TFLITE_SCHEMA_VERSION) {
		TF_LITE_REPORT_ERROR(error_reporter,
							 "Model provided is schema version %d not equal "
							 "to supported version %d.",
							 model->version(), TFLITE_SCHEMA_VERSION);
		return;
	}

	// This pulls in all the operation implementations we need.
	// NOLINTNEXTLINE(runtime-global-variables)
	static tflite::AllOpsResolver resolver;

	// Build an interpreter to run the model with.
	static tflite::MicroInterpreter static_interpreter(
	  model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
	interpreter = &static_interpreter;

	// Allocate memory from the tensor_arena for the model's tensors.
	TfLiteStatus allocate_status = interpreter->AllocateTensors();
	if (allocate_status != kTfLiteOk) {
		TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
		return;
	}

	// Obtain pointers to the model's input and output tensors.
	input = interpreter->input(0);
	if (!input) {
		printf("ERR: no input\n");
		return;
	}

	printf("input.dims.size = %d\n", input->dims->size);
	HAL_Delay(10);
	printf(" dims.x = %d\n", input->dims->data[0]);
	HAL_Delay(10);
	printf(" dims.y = %d\n", input->dims->data[0]);
	HAL_Delay(10);
	printf("input.type = %d\n", input->type);
	HAL_Delay(10);

	// Get the input quantization parameters
	float input_scale = input->params.scale;
	int input_zero_point = input->params.zero_point;
	printf("input scale(%f), zero_point(%d)\n", input_scale, input_zero_point);
	HAL_Delay(10);


	output = interpreter->output(0);
	if (!input) {
		printf("ERR: no output\n");
		return;
	}

	printf("output.dims.size = %d\n", output->dims->size);
	HAL_Delay(10);
	printf(" dims.x = %d\n", output->dims->data[0]);
	HAL_Delay(10);
	printf(" dims.y = %d\n", output->dims->data[0]);
	HAL_Delay(10);
	printf("output.type = %d\n", output->type);
	HAL_Delay(10);


	// Get the output quantization parameters
	float output_scale = output->params.scale;
	int output_zero_point = output->params.zero_point;
	printf("output scale(%f), zero_point(%d)\n", output_scale, output_zero_point);
	HAL_Delay(10);
}
