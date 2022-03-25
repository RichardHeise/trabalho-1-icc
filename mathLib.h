/**
 *  @file  mathLib.h
 *  @brief Arquivo com os cabeçalhos das funções de mathLib.c
 *  @date 06/04/2022
 *  @author Gabriel Lüders (GRR20190172)
 *  @author Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef MATH_SNL_H
#define MATH_SNL_H

/** @struct SVariables
 *  @brief Struct para guardar as variáveis da equação
 */
typedef struct SVariables{
  char** variables;
  int varAmount;
}variables;

/** @struct SFunction
 *  @brief Struct para guardar o valor da função, 
 *  da derivada e as variáveis da função
 */
typedef struct SFunction{
  void* f;
  void** dfs;
  variables* vars;
}function;

/**
 * @param char* func
 * @brief Função para construir uma function no formato de mathEval
 * @return Retorna um ponteiro para function
 */
function* functionConstructor(char* func);

/**
 * @param char* func
 * @brief Função para destruir a function do formato de mathEval
 */
void functionDestructor(function *func);

/**
 * @param function* f
 * @brief Função para resgatar as variáveis de uma function
 */
void showVariables(function* f);

/**
 * @param function* f
 * @brief Função para resgatar as derivadas de uma function
 */
void showDerivatives(function* f);

/**
 * @param function* f
 * @brief Função para resgatar uma function
 */
void showFunction(function* f);

#endif