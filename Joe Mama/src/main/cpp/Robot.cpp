/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/Timer.h>
#include <frc/Joystick.h>
#include <iostream>
#include <ctre/Phoenix.h>
#include <frc/Talon.h>
#include <frc/PWMTalonFX.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/SolenoidBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PowerDistributionPanel.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Timer.h>

using namespace frc;

Joystick stick{0};
PWMTalonFX motor{0};
Compressor compressor{0};
DoubleSolenoid piston{2, 3};
DoubleSolenoid piston2{0,1};
//Solenoid piston{4};
Timer timer;
//WPI_TalonFX * motor = new WPI_TalonFX(0);

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  SmartDashboard::PutData("Auto Modes", &m_chooser);
  compressor.SetClosedLoopControl(false);
  compressor.Start();
  timer.Reset();
  timer.Start();
  //piston.Set(false);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  //piston.Set(false);
  SmartDashboard::PutNumber("Pressure", compressor.GetPressureSwitchValue());
  SmartDashboard::PutNumber("Current", compressor.GetCompressorCurrent());
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  timer.Reset();
  timer.Start();
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  //piston.Set(false);
}

void Robot::TeleopPeriodic() {/*
  if (timer.Get() < 1.0) {
    piston.Set(false);
  }
  else if (timer.Get() < 2.0) {
    piston.Set(true);
  }
  else if (timer.Get() < 3.0) {
    piston.Set(false);
  }
  else if (timer.Get() < 4.0) {
    piston.Set(true);
  }
  else if (timer.Get() < 5.0) {
    piston.Set(false);
  }
  else if (timer.Get() < 6.0) {
    piston.Set(true);
  }
  else {
    piston.Set(false);
  }
  */
  /*if (stick.GetRawButton(1)) {
    motor.Set(0.75);
  }
  else if (stick.GetRawButton(2)) {
    motor.Set(-1.0);
  }
  if (stick.GetRawButton(4)) {
    piston.Set(true);
  }
  else if (stick.GetRawButton(3)) {
    piston.Set(false);
  }*/

  if (stick.GetRawButton(3)) {
    piston.Set(DoubleSolenoid::Value::kForward);
    piston2.Set(DoubleSolenoid::Value::kForward);
  }
  else if (stick.GetRawButton(4)) {
    piston.Set(DoubleSolenoid::Value::kReverse);
    piston2.Set(DoubleSolenoid::Value::kReverse);
  }
  else {
    piston.Set(DoubleSolenoid::Value::kOff);
    piston2.Set(DoubleSolenoid::Value::kOff);
  }

  //motor.Set(-stick.GetRawAxis(1));
  
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
