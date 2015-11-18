// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "TauriCharacter.generated.h"

UCLASS(config=Game)
class ATauriCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ATauriCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Turn Event, called when Mouse is moved left/right*/
	void Turn(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTurnPlayer(float Value);

	virtual void ServerTurnPlayer_Implementation(float Value);
	virtual bool ServerTurnPlayer_Validate(float Value);


	/** LookUp Event, called when Mouse is moved up/down */
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FRotator Viewport;

	void LookUp(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLookUpPlayer(float Value);

	virtual void ServerLookUpPlayer_Implementation(float Value);
	virtual bool ServerLookUpPlayer_Validate(float Value);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLookUp(FRotator vprt);

	virtual void MulticastLookUp_Implementation(FRotator vprt);
	virtual bool MulticastLookUp_Validate(FRotator vprt);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

