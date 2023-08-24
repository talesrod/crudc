#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_MATRICULA 50

typedef struct {
  char username[MAX_USERNAME];
  char matricula[MAX_MATRICULA];
  char address[200];
  char age[3];
} User;

void saveUsers(User users[], int count) {
  FILE *file = fopen("users.txt", "w");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

  for (int i = 0; i < count; i++) {
    fprintf(file, "%s %s %s %s\n", users[i].username, users[i].matricula,
            users[i].address, users[i].age);
  }

  fclose(file);
}

int loadUsers(User users[]) {
  FILE *file = fopen("users.txt", "r");
  if (file == NULL) {
    return 0;
  }

  int count = 0;
  while (fscanf(file, "%s %s %s %s", users[count].username,
                users[count].matricula, users[count].address,
                users[count].age) == 4) {
    count++;
  }

  fclose(file);
  return count;
}

void createUser(User users[], int *count) {
  if (*count >= MAX_USERS) {
    printf("Limite de usuários atingido.\n");
    return;
  }

  User newUser;
  printf("Digite o nome de usuário: ");
  scanf("%s", newUser.username);
  printf("Digite a matricula: ");
  scanf("%s", newUser.matricula);
  printf("Digite o endereço do usuário: ");
  scanf("%s", newUser.address);
  printf("Digite a idade: ");
  scanf("%s", newUser.age);

  users[*count] = newUser;
  (*count)++;

  saveUsers(users, *count);
  printf("Usuário criado com sucesso.\n");
}

void listUsers(User users[], int count) {
  printf("Lista de Usuários:\n");
  for (int i = 0; i < count; i++) {
    printf("Usuário: %s %s %s\n", users[i].username, users[i].address,
           users[i].age);
  }
}

int findUserIndex(User users[], int count, const char *username) {
  for (int i = 0; i < count; i++) {
    if (strcmp(users[i].username, username) == 0) {
      return i;
    }
  }
  return -1;
}

void editUser(User users[], int count) {
  char username[MAX_USERNAME];
  printf("Digite o nome de usuário que deseja editar: ");
  scanf("%s", username);

  int userIndex = findUserIndex(users, count, username);
  if (userIndex == -1) {
    printf("Usuário não foi encontrado.\n");
    return;
  }

  printf("Digite o novo nome de usuário: ");
  scanf("%s", users[userIndex].username);
  printf("Digite a nova matricula: ");
  scanf("%s", users[userIndex].matricula);
  printf("Digite o novo endereço de usuário: ");
  scanf("%s", users[userIndex].address);
  printf("Digite a nova idade: ");
  scanf("%s", users[userIndex].age);

  saveUsers(users, count);
  printf("Usuário atualizado com sucesso.\n");
}

void deleteUser(User users[], int *count) {
  char username[MAX_USERNAME];
  printf("Digite o nome de usuário que deseja excluir: ");
  scanf("%s", username);

  int userIndex = findUserIndex(users, *count, username);
  if (userIndex == -1) {
    printf("Usuário não encontrado.\n");
    return;
  }

  // Remover o usuário, movendo os outros usuários para preencher o espaço
  for (int i = userIndex; i < *count - 1; i++) {
    users[i] = users[i + 1];
  }

  (*count)--;
  saveUsers(users, *count);
  printf("Usuário excluído com sucesso.\n");
}

int main() {
  User users[MAX_USERS];
  int userCount = loadUsers(users);

  int choice;
  do {
    printf("\nOpções:\n");
    printf("1. Criar Usuário\n");
    printf("2. Listar Usuários\n");
    printf("3. Editar usuario\n");
    printf("4. Deletar Usuário\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      createUser(users, &userCount);
      break;
    case 2:
      listUsers(users, userCount);
      break;
    case 3:
      editUser(users, userCount);
      break;
    case 4:
      deleteUser(users, &userCount);
      break;
    case 5:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida.\n");
    }
  } while (choice != 5);

  return 0;
}

