// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// declare a log called InitLog
DECLARE_LOG_CATEGORY_EXTERN(InitLog, Log, All);
// declare a log called AILog
DECLARE_LOG_CATEGORY_EXTERN(AiLog, Log, All);
// declare a log called LabsLog
DECLARE_LOG_CATEGORY_EXTERN(LabsLog, Log, All);

#define LOG(msg, ...) UE_LOG(LabsLog, Log, TEXT(msg), ##__VA_ARGS__)
#define WARN(msg, ...) UE_LOG(LabsLog, Warning, TEXT(msg), ##__VA_ARGS__)
