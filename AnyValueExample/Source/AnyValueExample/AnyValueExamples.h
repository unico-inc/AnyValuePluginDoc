// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "AnyValue/AnyValue.h"

#include "GameFramework/Actor.h"


#include "AnyValueExamples.generated.h"

USTRUCT(BlueprintType)
struct FAnyValueExampleStruct
{
	GENERATED_BODY()
public:
	FAnyValueExampleStruct() = default;
	FAnyValueExampleStruct(int32 InIntValue, const FString& InStringValue)
	{
		IntValue = InIntValue;
		StringValue = InStringValue;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 IntValue = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString StringValue;
};


UCLASS(BlueprintType)
class AAnyValueExamples : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnyValue AnyValue;
	
	UFUNCTION(BlueprintCallable)
	void SetValueExample()
	{

		// assign int32
		AnyValue = 42;

		// assign FString
		FString Str = TEXT("str");
		AnyValue = Str;
		
		// assign USTRUCT
		FAnyValueExampleStruct Struct;
		Struct.IntValue = 42;
		Struct.StringValue = TEXT("str");
		AnyValue = Struct;

		// create int32
		AnyValue = FAnyValue::Create<int32>(42);

		// create FString
		AnyValue = FAnyValue::Create<FString>(TEXT("str"));
		
		// create USTRUCT
		AnyValue = FAnyValue::Create<FAnyValueExampleStruct>();

		// set USTRUCT
		FAnyValueExampleStruct& NewStruct = AnyValue.Set<FAnyValueExampleStruct>();
		NewStruct.IntValue = 42;

		// set UObject
		AnyValue = FAnyValue::Create<UObject*>(this);
		AnyValue.Set<UObject*>(this);

		// set UObject
		AnyValue = FAnyValue::FromObject(this);
		AnyValue = FAnyValue::FromSoftObjectPtr(this);
		AnyValue = FAnyValue::FromClass(GetClass());
		AnyValue = FAnyValue::FromSoftClassPtr(GetClass());
	}

	UFUNCTION(BlueprintCallable)
	void GetValueExample()
	{
		// get int32
		if (const int32* Value = AnyValue.As<int32>())
		{
			UE_LOG(LogTemp, Log, TEXT("int32: %d"), *Value);
		}

		// get FString
		if (const FString* Value = AnyValue.As<FString>())
		{
			UE_LOG(LogTemp, Log, TEXT("FString: %s"), **Value);
		}

		// get USTRUCT
		if (const auto* Value = AnyValue.As<FAnyValueExampleStruct>())
		{
			UE_LOG(LogTemp, Log, TEXT("FAnyValueExampleStruct: %d, '%s'"), Value->IntValue, *Value->StringValue);
		}

		
		// get UObject
		if (UObject*const* ObjectValuePtr = AnyValue.As<UObject*>())
		{
			if(AAnyValueExamples* ObjectValue = Cast<AAnyValueExamples>(*ObjectValuePtr))
			{
				UE_LOG(LogTemp, Log, TEXT("AAnyValueExamples: '%s'"), *ObjectValue->GetName());
			}
		}

		// get UObject
		if (AAnyValueExamples* ObjectValue = AnyValue.GetObjectValue<AAnyValueExamples>())
		{
			UE_LOG(LogTemp, Log, TEXT("AAnyValueExamples: '%s'"), *ObjectValue->GetName());
		}
		if (TSoftObjectPtr<UObject> ObjectValue = AnyValue.GetSoftObjectPtrValue())
		{
			UE_LOG(LogTemp, Log, TEXT("TSoftObjectPtr<UObject>: '%s'"), *ObjectValue.ToString());
		}
		if (TSubclassOf<AAnyValueExamples> ClassValue = AnyValue.GetClassValue<AAnyValueExamples>())
		{
			UE_LOG(LogTemp, Log, TEXT("TSubclassOf<AAnyValueExamples>: '%s'"), *ClassValue->GetName());
		}
		if (TSoftClassPtr<UObject> ClassValue = AnyValue.GetSoftClassPtrValue())
		{
			UE_LOG(LogTemp, Log, TEXT("TSoftClassPtr<UObject>: '%s'"), *ClassValue.ToString());
		}
	}
};




