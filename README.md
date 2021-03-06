# AnyValue Plugin


## UE4 Marketplace

[Marketplace](https://www.unrealengine.com/marketplace/en-US/store)

# Summary

`FAnyValue` is a type that can hold and get values of various types, like `std::any` in C++.

Various primitive types, string types, USTRUCT structures, UObjects, etc. are supported.

It can be used when you want to handle types loosely, such as passing data to a common widget or parameters for a simple script.

# Installing the plugin

Install the plugin into the engine from the [Marketplace](https://www.unrealengine.com/marketplace/en-US/store).

Make sure the plugin is activated from "Edit" > "Plugins".

![Enabling plugins](./img/editor_plugin.png)

# How to use in Blueprint

## Basic usage

1. Open a Blueprint asset.
   
2. Add a variable from VARIABLES in the My Blueprint tab and set the type to AnyValue.

![tutorial_1](./img/tutorial_1.png)

3. Once the blueprint is compiled, initial values for variables can be set from the Details tab.

![tutorial_2](./img/tutorial_2.png)

4. You can set and get values by calling the functions provided for each type.
For details on how to set and get values for each type, see [here](#how-to-set-and-get-each-type).


## How to set and get each type

### Setting and getting structures

- Get Struct from AnyValue
- Set Struct in AnyValue

![Setting and getting structures](./img/bp5_1.png)

### Setting and getting primitive and string types

- ToAnyValue (boolean)
- GetBoolValue
- ToAnyValue (byte)
- GetByteValue
- ToAnyValue (integer)
- GetIntValue
- ToAnyValue (Int64)
- GetInt64Value
- ToAnyValue (float)
- GetFloatValue
- ToAnyValue (String)
- GetStringValue
- ToAnyValue (Name)
- GetNameValue
- ToAnyValue (Text)
- GetTextValue
  
![Setting and getting primitive and string types](./img/bp5_2.png)

![Setting and getting primitive and string types](./img/bp5_3.png)

### Setting and getting object-related types

- ToAnyValue (Object)
- GetObjectFromAnyValue
- ToAnyValue (SoftObjectReference)
- GetSoftObjectReferenceFromAnyValue
- ToAnyValue (Class)
- GetClassFromAnyValue
- ToAnyValue (SoftClassReference)
- GetSoftClassReferenceFromAnyValue

![Setting and getting object-related types](./img/bp5_4.png)

![Setting and getting object-related types](./img/bp5_5.png)

# Usage in C++

Add a dependency on the `AnyValue` module to the Build.cs file of the module you want to use.

```cs
public class AnyValueExample : ModuleRules
{
	public AnyValueExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"AnyValue",		// Add dependent modules
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
```

[AnyValueExample/Source/AnyValueExample/AnyValueExamples.h](AnyValueExample/Source/AnyValueExample/AnyValueExamples.h)

Add header includes.

```cpp
#include "AnyValue/AnyValue.h"
```

## Setting and Getting Values

### Set Primitive type, string type, and structure

A value can be set by assigning a value to FAnyValue.

```cpp
    FAnyValue AnyValue;

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
```

The `FAnyValue :: Create` function is provided as an initialization method to specify the type.

```cpp
    // create int32
    AnyValue = FAnyValue::Create<int32>(42);

    // create FString
    AnyValue = FAnyValue::Create<FString>(TEXT("str"));
    
    // create USTRUCT
    AnyValue = FAnyValue::Create<FAnyValueExampleStruct>();
```

The `Set` function returns a reference to the set value.
It can be used to set a value or call a function from the returned value.

```cpp
    // set USTRUCT
    FAnyValueExampleStruct& NewStruct = AnyValue.Set<FAnyValueExampleStruct>();
    NewStruct.IntValue = 42;
```

### Getting Primitive, String, and Structure Types

You can use the `As` function to get the value.
If the `As` function cannot get the specified type, it returns nullptr.

```cpp
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
```

### Setting UObject-related types

To avoid confusion with the `UScriptStruct*` constructor, UObject-related types cannot be initialized or assigned with the normal constructor.

Please use the following dedicated initialization functions.

```cpp
    // set UObject
    AnyValue = FAnyValue::FromObject(this);
    AnyValue = FAnyValue::FromSoftObjectPtr(this);
    AnyValue = FAnyValue::FromClass(GetClass());
    AnyValue = FAnyValue::FromSoftClassPtr(GetClass());
```

### Getting UObject-related types

UObject-related types can also be obtained like other types by calling `As<UObject*>()`.

The return value will be `UObject**`, so a two-step check is required to use the object.

```cpp
	// get UObject
    if (UObject*const* ObjectValuePtr = AnyValue.As<UObject*>())
    {
        if(AAnyValueExamples* ObjectValue = Cast<AAnyValueExamples>(*ObjectValuePtr))
        {
            UE_LOG(LogTemp, Log, TEXT("AAnyValueExamples: '%s'"), *ObjectValue->GetName());
        }
    }
```

For this reason, UObject-related types have dedicated get functions as follows.

```cpp
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
```

