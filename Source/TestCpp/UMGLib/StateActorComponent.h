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
	/// 更新関数
	/// </summary>
	/// <returns>現在のステートを返す</returns>
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
	/// 次のステートに遅延切り替え処理
	/// </summary>
	/// <param name="in_nextState">次のステート</param>
	void ChangeState(FText in_nextState)
	{
		NextState = in_nextState;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// ステートを取得
	/// </summary>
	/// <returns>現在のステートを返す</returns>
	FText GetState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "StateComponent")
	/// <summary>
	/// State Count 初期化
	/// </summary>
	void InitStateCounter() {
		counter = 0;
		CurrentState = FText::FromString(TEXT("None"));
		NextState = FText::FromString(TEXT("None"));
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// カウント値取得
	/// </summary>
	/// <returns>cuonterを返す</returns>
	int32 GetCounter() const { return counter; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StateComponent")
	/// <summary>
	/// カウント開始時かどうかチェック
	/// </summary>
	/// <returns>true:cuonter==0のとき,false:一度でも処理した場合</returns>
	bool IsFirst() const { return counter == 0; }

protected:

	FText CurrentState;
	FText NextState;
	int32 counter;
};