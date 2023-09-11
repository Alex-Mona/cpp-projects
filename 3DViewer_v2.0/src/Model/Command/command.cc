#include "command.h"

namespace s21 {
void Invoker::Execute(Command* command, Operation operation, double value) {
  command->Execute(operation, value);
  delete command;
}

RotateCommand::RotateCommand(Strategy* strategy) { strategy_ = strategy; }

void RotateCommand::Execute(Operation role, double value) {
  strategy_->Execute(role, value);
}

MoveCommand::MoveCommand(Strategy* strategy) { strategy_ = strategy; }

void MoveCommand::Execute(Operation role, double value) {
  strategy_->Execute(role, value);
}

ScaleCommand::ScaleCommand(Strategy* strategy) { strategy_ = strategy; }

void ScaleCommand::Execute(Operation role, double value) {
  strategy_->Execute(role, value);
}
}  // namespace s21
