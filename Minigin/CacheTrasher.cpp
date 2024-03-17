#include <regex>
#include <iostream>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <numeric>
#include "CacheTrasher.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"


using namespace Engine;

CacheTrasher::CacheTrasher(GameObject* gameObjectParentPointer) :
	GameObjectComponent(COMPONENT_TYPE::CacheTrasher, COMPONENT_TYPENAME_CACHETRASHER, gameObjectParentPointer)
	
{

    m_ArrayOfIntegers.fill(int{ 1 });
    m_ArrayOfGameObjects.fill(GameObject3D{ });
    m_ArrayOfAltGameObjects.fill(GameObject3DAlt{ nullptr, 1 });
    RunExerciseOneCalculations();
    RunExerciseTwoCalculations();

}

void CacheTrasher::Update(float deltaTime)
{
    deltaTime;

    if (m_UpdateExerciseOne)
    {
        RunExerciseOneCalculations();
    }

    if (m_UpdateExerciseTwo)
    {
        RunExerciseTwoCalculations();
    }



}

void CacheTrasher::RenderUI(float xPosition, float yPosition, float rotation)
{
    xPosition;
    yPosition;
    rotation;

    ImGui::SetNextWindowPos(ImVec2{0, 100});

    ImGui::Begin("ExerciseOne");

    static float horizontalLabels[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024  };


    ImGui::PlotLines("Integers", m_ExerciseOneOutput, IM_ARRAYSIZE(m_ExerciseOneOutput));
    if (ImGui::Button("Run Exercise One Calculations"))
    {
        m_UpdateExerciseOne = true;
    }
 
    ImGui::End();


    ImGui::SetNextWindowPos(ImVec2{ 200, 100 });


    ImGui::Begin("ExerciseTwo");

    ImGui::PlotLines("GameObject", m_ExerciseTwoPartOneOutput, IM_ARRAYSIZE(m_ExerciseTwoPartOneOutput));

    ImGui::PlotLines("GameObjectAlt", m_ExerciseTwoPartTwoOutput, IM_ARRAYSIZE(m_ExerciseTwoPartTwoOutput));

    if (ImGui::Button("Run Exercise Two Calculations"))
    {
        m_UpdateExerciseTwo = true;
    }

    ImGui::End();

}

void CacheTrasher::RunExerciseOneCalculations()
{

    std::cout << "\nIterating over integer array\n";

    std::vector<float> rawResults;

    for (int iteration{}; iteration < m_RepetitionsToDo; ++iteration)
    {
        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < m_ArraySize; i += stepSize)
            {
                m_ArrayOfIntegers[i] *= 2;
            }

            rawResults.push_back(float(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()));
        }
    }


    ProccessRawData(rawResults, m_ExerciseOneOutput);
    m_UpdateExerciseOne = false;

}

void CacheTrasher::RunExerciseTwoCalculations()
{



    std::cout << "\nIterating over GameObject3D array\n";


    std::vector<float> rawResults;

    for (int iteration{}; iteration < m_RepetitionsToDo; ++iteration)
    {
        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < m_ArraySize; i += stepSize)
            {
                m_ArrayOfGameObjects[i].ID *= 2;
            }

            rawResults.push_back(float(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()));

        }
    }

    ProccessRawData(rawResults, m_ExerciseTwoPartOneOutput);

    rawResults.clear();

    std::cout << "\nIterating over GameObject3DAlt array\n";


    for (int iteration{}; iteration < m_RepetitionsToDo; ++iteration)
    {
        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < m_ArraySize; i += stepSize)
            {
                m_ArrayOfAltGameObjects[i].ID *= 2;
            }

            rawResults.push_back(float(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()));

        }
    }



    ProccessRawData(rawResults, m_ExerciseTwoPartTwoOutput);

    m_UpdateExerciseTwo = false;
}

void CacheTrasher::ProccessRawData(const std::vector<float>& vectorOfRawData, float* outputTarget)
{


    for (int set{}; set < m_StepCount; ++set)
    {
        std::multiset<float> resultSet;
        for (int rep{}; rep < m_RepetitionsToDo; ++rep)
        {
            resultSet.insert(vectorOfRawData[m_StepCount * rep + set]);
        }
        std::multiset<float>::iterator iterator = resultSet.begin();

        for (int i{ 1 }; i < (m_RepetitionsToDo - 1); ++i)
        {
            ++iterator;
        }

        resultSet.erase(iterator);
        resultSet.erase(resultSet.begin());
        
        
  
        outputTarget[set] = float(std::accumulate(resultSet.begin(), resultSet.end(), 0.f) / (m_RepetitionsToDo - 2));

    }




}