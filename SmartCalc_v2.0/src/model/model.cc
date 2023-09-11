#include "model.h"

s21::Model::Model(const s21::Model &value)
    : data_(0), temp_num_(""), check_num_(false) {
  while (!this->stack_calc.empty()) {
    this->stack_calc.pop_back();
  }
  this->stack_calc = value.stack_calc;
}

void s21::Model::Plus(double a) { this->data_ += a; }
void s21::Model::Minus(double a) { this->data_ -= a; }
void s21::Model::Div(double a) { this->data_ /= a; }
void s21::Model::Mult(double a) { this->data_ *= a; }
void s21::Model::Mod(double a) { this->data_ = fmod(data_, a); }
void s21::Model::Cos(double a) { this->data_ = std::cos(a); }
void s21::Model::Sin(double a) { this->data_ = std::sin(a); }
void s21::Model::Tan(double a) { this->data_ = std::tan(a); }
void s21::Model::Acos(double a) { this->data_ = std::acos(a); }
void s21::Model::Asin(double a) { this->data_ = std::asin(a); }
void s21::Model::Atan(double a) { this->data_ = std::atan(a); }
void s21::Model::Sqrt(double a) { this->data_ = std::sqrt(a); }
void s21::Model::Ln(double a) { this->data_ = std::log(a); }
void s21::Model::Log(double a) { this->data_ = std::log10(a); }
void s21::Model::Reset() { this->data_ = 0; }
double s21::Model::GetData() { return this->data_; }
void s21::Model::Pow(double a) { this->data_ = std::pow(data_, a); }
list<s21::ListCalc> s21::Model::GetStack() { return this->stack_calc; }

double s21::Model::ReadNum() {
  double num = atof(temp_num_.data());
  temp_num_ = "";
  temp_num_.resize(255);
  return num;
}

void s21::Model::AllProfit(double &profit, double &percent_money) {
  profit += percent_money;
  percent_money = 0;
}

void s21::Model::PushStack(type_action act, type_priority priority,
                           double data) {
  ListCalc temp(act, priority, data);
  this->stack_calc.push_back(temp);
  check_num_ = false;
}

void s21::Model::ReverseStack() {
  list<ListCalc> new_stack;
  while (!stack_calc.empty()) {
    new_stack.push_back(stack_calc.back());
    stack_calc.pop_back();
  }
  std::swap(stack_calc, new_stack);
}

void s21::Model::SortStation() {
  this->ReverseStack();
  s21::Model result;
  s21::Model temp;
  while (!stack_calc.empty()) {
    int menu = stack_calc.back().prt;
    switch (menu) {
      case 0:
        result.PushStack(NUMBER, NUM, stack_calc.back().num);
        break;
      default:
        this->AddTempStack(temp, result);
        break;
    }
    stack_calc.pop_back();
  }
  while (!temp.stack_calc.empty()) {
    if (temp.stack_calc.back().type != LEFT &&
        temp.stack_calc.back().type != RIGHT) {
      result.PushStack(temp.stack_calc.back().type, temp.stack_calc.back().prt,
                       0);
    }
    temp.stack_calc.pop_back();
  }
  stack_calc = result.stack_calc;
}

void s21::Model::AddTempStack(s21::Model &temp, s21::Model &result) {
  if (!temp.stack_calc.empty()) {
    if ((stack_calc.back().prt > temp.stack_calc.back().prt) ||
        (stack_calc.back().type == LEFT) || stack_calc.back().type == POW) {
      temp.PushStack(stack_calc.back().type, stack_calc.back().prt, 0);
    } else {
      if (stack_calc.back().type == RIGHT) {
        while ((!temp.stack_calc.empty()) &&
               (temp.stack_calc.back().type != LEFT)) {
          result.PushStack(temp.stack_calc.back().type,
                           temp.stack_calc.back().prt, 0);
          temp.stack_calc.pop_back();
        }
      } else {
        result.PushStack(temp.stack_calc.back().type,
                         temp.stack_calc.back().prt, 0);
        temp.stack_calc.pop_back();
      }
      temp.PushStack(stack_calc.back().type, stack_calc.back().prt, 0);
      if (result.stack_calc.back().type < COS) {
        if (temp.stack_calc.back().type == RIGHT) temp.stack_calc.pop_back();
        if (temp.stack_calc.back().type == LEFT) temp.stack_calc.pop_back();
      }
    }
  } else {
    temp.PushStack(stack_calc.back().type, stack_calc.back().prt, 0);
  }
}

double s21::Model::ScanLineEdit(string input, double in_x) {
  for (size_t i = 0, x = 0; i < (input.length() + 1); i++) {
    switch (input[i]) {
      case '+':
        this->AddTokenPlus(input, x, i);
        break;
      case '-':
        this->AddTokenMinus(input, x, i);
        break;
      case '*':
        this->AddTokenMult(x);
        break;
      case '/':
        this->AddTokenDiv(x);
        break;
      case '^':
        this->AddTokenPow(x);
        break;
      case 'm':
        this->AddTokenMod(x);
        break;
      case 'c':
        this->AddTokenCos(input, i);
        break;
      case 's':
        this->AddTokenSin(input, i);
        this->AddTokenSqrt(input, i);
        break;
      case 't':
        this->AddTokenTan(input, i);
        break;
      case 'a':
        this->AddTokenAcos(input, i);
        this->AddTokenAsin(input, i);
        this->AddTokenAtan(input, i);
        break;
      case 'l':
        this->AddTokenLn(input, i);
        this->AddTokenLog(input, i);
        break;
      case '(':
        this->AddTokenLeft();
        break;
      case ')':
        this->AddTokenRight(x);
        break;
      default:
        this->ReadNumber(input, x, i, in_x);
        break;
    }
  }
  temp_num_.resize(255);
  this->SortStation();
  return this->Calculation(this->stack_calc);
}

void s21::Model::AddTokenPlus(const std::string &input, size_t &x,
                              const size_t &position) {
  if (input[position - 1] == '(') {
    temp_num_[x++] = input[position];
  } else if (input[position - 1] == 'e' || input[position - 1] == 'E') {
    temp_num_[x++] = input[position];
    check_num_ = true;
  } else {
    if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
    this->PushStack(PLUS, LOW_PR, 0);
    x = 0;
  }
}

void s21::Model::AddTokenMinus(const std::string &input, size_t &x,
                               const size_t &position) {
  if (input[position - 1] == '(') {
    temp_num_[x++] = input[position];
  } else {
    if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
    this->PushStack(MINUS, LOW_PR, 0);
    x = 0;
  }
}

void s21::Model::AddTokenDiv(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  this->PushStack(DIV, MEDIUM_PR, 0);
  x = 0;
}

void s21::Model::AddTokenMult(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  this->PushStack(MULT, MEDIUM_PR, 0);
  x = 0;
}

void s21::Model::AddTokenPow(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  this->PushStack(POW, HIGH_PR, 0);
  ;
  x = 0;
}

void s21::Model::AddTokenMod(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  this->PushStack(MOD, MEDIUM_PR, 0);
  x = 0;
}

void s21::Model::AddTokenCos(const std::string &input, size_t &position) {
  if (input[position + 1] == 'o' ? input[position + 2] == 's' ? 1 : 0 : 0) {
    position += 2;
    this->PushStack(COS, HIGH_PR, 0);
    ;
  }
}

void s21::Model::AddTokenSin(const std::string &input, size_t &position) {
  if (input[position + 1] == 'i' ? input[position + 2] == 'n' ? 1 : 0 : 0) {
    position += 2;
    this->PushStack(SIN, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenTan(const std::string &input, size_t &position) {
  if (input[position + 1] == 'a' ? input[position + 2] == 'n' ? 1 : 0 : 0) {
    position += 2;
    this->PushStack(TAN, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenAcos(const std::string &input, size_t &position) {
  if (input[position + 1] == 'c'
          ? input[position + 2] == 'o' ? input[position + 3] == 's' ? 1 : 0 : 0
          : 0) {
    position += 3;
    this->PushStack(ACOS, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenAsin(const std::string &input, size_t &position) {
  if (input[position + 1] == 's'
          ? input[position + 2] == 'i' ? input[position + 3] == 'n' ? 1 : 0 : 0
          : 0) {
    position += 3;
    this->PushStack(ASIN, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenAtan(const std::string &input, size_t &position) {
  if (input[position + 1] == 't'
          ? input[position + 2] == 'a' ? input[position + 3] == 'n' ? 1 : 0 : 0
          : 0) {
    position += 3;
    this->PushStack(ATAN, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenSqrt(const std::string &input, size_t &position) {
  if (input[position + 1] == 'q'
          ? input[position + 2] == 'r' ? input[position + 3] == 't' ? 1 : 0 : 0
          : 0) {
    position += 3;
    this->PushStack(SQRT, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenLn(const std::string &input, size_t &position) {
  if (input[position + 1] == 'n' ? 1 : 0) {
    position += 1;
    this->PushStack(LN, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenLog(const std::string &input, size_t &position) {
  if (input[position + 1] == 'o' ? input[position + 2] == 'g' ? 1 : 0 : 0) {
    position += 2;
    this->PushStack(LOG, HIGH_PR, 0);
  }
}

void s21::Model::AddTokenLeft() { this->PushStack(LEFT, LLOW_PR, 0); }

void s21::Model::AddTokenRight(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  this->PushStack(RIGHT, LLOW_PR, 0);
  x = 0;
}

void s21::Model::AddNumber(size_t &x) {
  if (check_num_) this->PushStack(NUMBER, NUM, this->ReadNum());
  x = 0;
}

void s21::Model::ReadNumber(const std::string &input, size_t &x,
                            const size_t &position, const double &in_x) {
  switch (input[position]) {
    case 'x':
      this->PushStack(NUMBER, NUM, in_x);
      break;
    case '.':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '0':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '1':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '2':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '3':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '4':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '5':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '6':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '7':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '8':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case '9':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case 'e':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    case 'E':
      temp_num_[x++] = input[position];
      check_num_ = true;
      break;
    default:
      this->AddNumber(x);
      break;
  }
}

double s21::Model::Calculation(list<ListCalc> &head) {
  this->ReverseStack();
  s21::Model temp;
  this->Reset();
  double b;
  while (!head.empty()) {
    if (head.back().prt == 0) {
      temp.PushStack(stack_calc.back().type, stack_calc.back().prt,
                     stack_calc.back().num);
    } else if ((stack_calc.back().prt > 0) &&
               (stack_calc.back().type < COS && stack_calc.back().type > 0)) {
      if (!temp.stack_calc.empty()) {
        b = temp.stack_calc.back().num;
        temp.stack_calc.pop_back();
        data_ = temp.stack_calc.back().num;
        if (!temp.stack_calc.empty()) temp.stack_calc.pop_back();
      }
      temp.PushStack(NUMBER, NUM, this->Arithmetic(b, stack_calc.back().type));
    } else if ((stack_calc.back().prt > 0) && (stack_calc.back().type > MOD &&
                                               stack_calc.back().type < LEFT)) {
      if (!temp.stack_calc.empty()) {
        b = temp.stack_calc.back().num;
        temp.stack_calc.pop_back();
        temp.PushStack(NUMBER, NUM,
                       this->Trigonometry(b, stack_calc.back().type));
      }
    }
    head.pop_back();
  }
  if (!temp.stack_calc.empty()) {
    data_ = temp.stack_calc.back().num;
  }
  return data_;
}

double s21::Model::Arithmetic(double b, int symbol) {
  if (symbol == PLUS) {
    this->Plus(b);
  }
  if (symbol == MINUS) {
    this->Minus(b);
  }
  if (symbol == DIV) {
    this->Div(b);
  }
  if (symbol == MULT) {
    this->Mult(b);
  }
  if (symbol == POW) {
    this->Pow(b);
  }
  if (symbol == MOD) {
    this->Mod(b);
  }
  return data_;
}

double s21::Model::Trigonometry(double a, int symbol) {
  if (symbol == COS) {
    this->Cos(a);
  }
  if (symbol == SIN) {
    this->Sin(a);
  }
  if (symbol == TAN) {
    this->Tan(a);
  }
  if (symbol == ACOS) {
    this->Acos(a);
  }
  if (symbol == ASIN) {
    this->Asin(a);
  }
  if (symbol == ATAN) {
    this->Atan(a);
  }
  if (symbol == SQRT) {
    this->Sqrt(a);
  }
  if (symbol == LN) {
    this->Ln(a);
  }
  if (symbol == LOG) {
    this->Log(a);
  }
  return data_;
}

double s21::Model::AnnuityCalculator(const double &sum_credit,
                                     const double &percent, const int &size,
                                     double &month_sum, double &month_percent,
                                     double &remains) {
  double percent_year = (percent / 100) / (size <= 12 ? size : 12);
  double result =
      (sum_credit * percent_year * std::pow(1 + percent_year, size)) /
      (std::pow(1 + percent_year, size) - 1);
  month_percent = remains * percent_year;
  month_sum = result - month_percent;
  remains -= month_sum;
  return result;
}

double s21::Model::DifferentiatedCalculator(const double &sum_credit,
                                            const double &percent,
                                            const int &size, double &month_sum,
                                            double &month_percent,
                                            double &remains) {
  month_percent = (remains * (percent / 100)) / (size <= 12 ? size : 12);
  month_sum = sum_credit / size;
  double result = month_sum + month_percent;
  remains -= (sum_credit / size);
  return result;
}

double s21::Model::DepositCalculator(
    const std::vector<std::pair<std::string, double>> &add_sub_money,
    const std::string &data, const double &percent, double &month_percent,
    double &profit) {
  double result = 0;
  for (auto &&value : add_sub_money) {
    if (value.first == data) {
      result += value.second;
    }
  }
  month_percent = profit * percent * 30 / 365 / 100;
  profit += month_percent;
  return result;
}
