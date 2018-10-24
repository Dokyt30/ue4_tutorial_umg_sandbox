// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTCPP_API UStateActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "StateComponent")
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	/// <returns>���݂̃X�e�[�g��Ԃ�</returns>
	FText Update()
	{
		counter++;
		if (!NextState.EqualTo(FText::FromString(TEXT("None")))) {
			CurrentState = NextState;
			counter = 0;
			NextState = FText::FromString(TEXT("None"));
		}
		return CurrentState;
	}


	UFUNCTION(BlueprintCallable, Category = "StateComponent")
	/// <summary>
	/// ���̃X�e�[�g�ɒx���؂�ւ�����
	/// </summary>
	/// <param name="in_nextState">���̃X�e�[�g</param>
	void ChangeState(FText in_nextState)
	{
		NextState = in_nextState;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// �X�e�[�g���擾
	/// </summary>
	/// <returns>���݂̃X�e�[�g��Ԃ�</returns>
	FText GetState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "StateComponent")
	/// <summary>
	/// State Count ������
	/// </summary>
	void InitStateCounter() {
		counter = 0;
		CurrentState = FText::FromString(TEXT("None"));
		NextState = FText::FromString(TEXT("None"));
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// �J�E���g�l�擾
	/// </summary>
	/// <returns>cuonter��Ԃ�</returns>
	int32 GetCounter() const { return counter; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// �J�E���g�J�n�����ǂ����`�F�b�N
	/// </summary>
	/// <returns>true:cuonter==0�̂Ƃ�,false:��x�ł����������ꍇ</returns>
	bool IsFirst() const { return counter == 0; }

protected:

	FText CurrentState;
	FText NextState;
	int32 counter;
};