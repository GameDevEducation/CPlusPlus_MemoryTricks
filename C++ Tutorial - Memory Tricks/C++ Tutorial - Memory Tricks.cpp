// C++ Tutorial - Memory Tricks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

struct SimpleStruct
{
	static constexpr size_t Value3Length = 4;

	int Value1;					// 4
	float Value2;				// 4

	int Value3[Value3Length];	// 4 * 4 = 16

	//std::string Value4;
	//std::vector<float> Value5;
};

class DemoClass_Parent
{
public:
	static constexpr size_t Value3Length = 4;

	int Value1;					// 4
	float Value2;				// 4

	int Value3[Value3Length];	// 4 * 4 = 16

	//virtual void Test()
	//{
	//	std::cout << Value2 << std::endl;
	//}
};

class DemoClass_Child : public DemoClass_Parent
{
public:
	int Value4;
};

int main()
{
	{
		std::cout << "Simple Types" << std::endl;

		const size_t numFloats = 4;

		// create a buffer to hold 4 floats
		uint8_t* byteBuffer = new uint8_t[numFloats * sizeof(float)];

		for (size_t index = 0; index < numFloats; ++index)
		{
			float* valuePtr1 = reinterpret_cast<float*>(byteBuffer + index * sizeof(float));
			float* valuePtr2 = reinterpret_cast<float*>(byteBuffer) + index;

			*valuePtr1 = index + 0.123f;

			std::cout << index << ": " << *valuePtr2 << std::endl;
		}

		// free the buffer
		delete[] byteBuffer;
	}

	{
		std::cout << "Less Simple Types" << std::endl;

		const size_t numElements = 4;

		// create a buffer to hold 4 floats
		uint8_t* byteBuffer = new uint8_t[numElements * sizeof(SimpleStruct)];

		std::cout << "Size is " << sizeof(SimpleStruct) << std::endl;

		for (size_t index = 0; index < numElements; ++index)
		{
			SimpleStruct* valuePtr = reinterpret_cast<SimpleStruct*>(byteBuffer) + index;

			valuePtr->Value1 = (int)index;
			valuePtr->Value2 = index + 0.123f;
			//valuePtr->Value4 = "Hello!";
			//valuePtr->Value5.push_back(index);

			for (size_t childIndex = 0; childIndex < SimpleStruct::Value3Length; ++childIndex)
			{
				valuePtr->Value3[childIndex] = childIndex;
				std::cout << childIndex << " = " << valuePtr->Value3[childIndex] << std::endl;
			}

			std::cout << index << ": " << valuePtr->Value1 << ", "  
									   << valuePtr->Value2 << std::endl;
		}

		// free the buffer
		delete[] byteBuffer;
	}

	{
		std::cout << "Even Less Simple Types" << std::endl;

		const size_t numElements = 4;

		// create a buffer to hold 4 floats
		uint8_t* byteBuffer = new uint8_t[numElements * sizeof(DemoClass_Child)];

		std::cout << "Size is " << sizeof(DemoClass_Child) << std::endl;

		for (size_t index = 0; index < numElements; ++index)
		{
			DemoClass_Child* valuePtr = reinterpret_cast<DemoClass_Child*>(byteBuffer) + index;

			valuePtr->Value1 = (int)index;
			valuePtr->Value2 = index + 0.123f;
			valuePtr->Value4 = index;

			//valuePtr->Test();

			for (size_t childIndex = 0; childIndex < DemoClass_Child::Value3Length; ++childIndex)
			{
				valuePtr->Value3[childIndex] = childIndex;
				std::cout << childIndex << " = " << valuePtr->Value3[childIndex] << std::endl;
			}

			std::cout << index << ": " << valuePtr->Value1 << ", "
									   << valuePtr->Value2 << ", "
									   << valuePtr->Value4 << std::endl;
		}

		// free the buffer
		delete[] byteBuffer;
	}
}
