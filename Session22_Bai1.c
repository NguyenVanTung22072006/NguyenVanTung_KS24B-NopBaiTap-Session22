#include <stdio.h>

struct SinhVien{
    char id[50];
    char name[50];
    int age;
};
struct SinhVien sv[100];
int numberStudent=0;
void getStudentByFile();
void printStudent();
void addStudent();
void saveStudent();
void updateStudent();
void deleteStudent();
void searchStudent();

int main(){
    getStudentByFile();
    int choose;
    do{
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim thong tin sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Thoat\n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choose);
        getchar();
        switch (choose){
            case 1:
                printStudent();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
        }
    }while(choose!=7);

    return 0;
}

void getStudentByFile(){
    FILE *file;
    file=fopen("sinhvien.bin", "rb");
    if(file==NULL){
        printf("Khong the mo file\n");
        return;
    }
    numberStudent=fread(sv, sizeof(struct SinhVien), 100, file);
    fclose(file);
}
void printStudent(){
    if(numberStudent==0){
        printf("Khong co sinh vien\n");
        return;
    }
    for(int i=0; i<numberStudent; i++){
        printf("Thong tin sinh vien thu %d\n", i+1);
        printf("Ma SV: %s\n", sv[i].id);
        printf("Ten SV: %s\n", sv[i].name);
        printf("Tuoi SV: %d\n", sv[i].age);
    }
}
void addStudent(){
    if(numberStudent>=100){
        printf("Danh sach sinh vien da day\n");
        return;
    }
    struct SinhVien sv1;
    printf("Nhap ID: ");
    fgets(sv1.id, sizeof(sv1.id), stdin);
    sv1.id[strcspn(sv1.id, "\n")]='\0';
    printf("Nhap ten: ");
    fgets(sv1.name, sizeof(sv1.name), stdin);
    sv1.name[strcspn(sv1.name, "\n")]='\0';
    printf("Nhap tuoi: ");
    scanf("%d", &sv1.age);
    getchar();
    sv[numberStudent]=sv1;
    numberStudent++;
    saveStudent();
}
void saveStudent(){
    FILE *file;
    file=fopen("sinhvien.bin", "wb");
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file);
    fclose(file);
}
void updateStudent(){
    char id[50];
    printf("Nhap ID sinh vien can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")]='\0';
    for(int i=0; i<numberStudent; i++){
        if(strcmp(sv[i].id, id) == 0){
            printf("Nhap ten moi: ");
            fgets(sv[i].name, sizeof(sv[i].name), stdin);
            sv[i].name[strcspn(sv[i].name, "\n")]='\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &sv[i].age);
            getchar();
            saveStudent();
            printf("Cap nhat thong tin thanh cong\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}
void deleteStudent(){
    char id[50];
    printf("Nhap ID sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] ='\0';
    for(int i=0; i<numberStudent; i++){
        if (strcmp(sv[i].id, id)==0){
            for(int j=i; j<numberStudent-1; j++){
                sv[j]=sv[j+1];
            }
            numberStudent--;
            saveStudent();
            printf("Xoa sinh vien thanh cong\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}
void searchStudent(){
    char id[50];
    printf("Nhap ID sinh vien can tim: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")]='\0';
    for(int i=0; i<numberStudent; i++){
        if(strcmp(sv[i].id, id)==0){
            printf("Thong tin sinh vien:\n");
            printf("Ma SV: %s\n", sv[i].id);
            printf("Ten SV: %s\n", sv[i].name);
            printf("Tuoi SV: %d\n", sv[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}
