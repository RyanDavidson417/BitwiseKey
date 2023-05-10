// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLibInClass.h"

FVector UBPLibInClass::MoveTowards(const FVector &startPos, const FVector &endPos, float maxDist) 
{
    FVector direction = endPos - startPos;

    if(maxDist >= direction.Length())//if we're within maxDistance of the destination
    {
        return endPos; //just return the destination
    }
    
    direction.Normalize();
    FVector directionStep = direction * maxDist;
    
    
    return startPos+directionStep;
}
