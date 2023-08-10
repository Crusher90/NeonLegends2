// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLSettingsWidget : public UNLParentWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCheckBox> CB_Vibration;

protected:
	virtual bool Initialize() override;
	
	UFUNCTION()
	void OnCheckedStateChanged_Vibration(bool Value);
};
