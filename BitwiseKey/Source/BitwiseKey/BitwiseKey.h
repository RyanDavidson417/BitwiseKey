// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// declare a log called InitLog
DECLARE_LOG_CATEGORY_EXTERN(InitLog, Log, All);
// declare a log called AILog
DECLARE_LOG_CATEGORY_EXTERN(AiLog, Log, All);


#define LOG(msg, ...) UE_LOG(InitLog, Log, TEXT(msg), ##__VA_ARGS__)
#define WARN(msg, ...) UE_LOG(InitLog, Warning, TEXT(msg), ##__VA_ARGS__)
#define ERROR(msg, ...) UE_LOG(InitLog, Error, TEXT(msg), ##__VA_ARGS__)

#define AILOG(msg, ...) UE_LOG(AiLog, Log, TEXT(msg), ##__VA_ARGS__)
#define AIWARN(msg, ...) UE_LOG(AiLog, Warning, TEXT(msg), ##__VA_ARGS__)