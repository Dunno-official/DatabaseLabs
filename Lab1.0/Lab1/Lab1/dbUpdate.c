#pragma pack(1)
#include "dbUpdate.h"
#include "dbFilesHandler.h"
#include "dbRead.h"
#include "dbStructures.h"
#include <stdio.h>

void updateM() {
  shop updShop = getM();
  if (updShop.isActive) {
    printf("\\\\ Enter new address: ");
    fflush(stdin);
    gets(updShop.address);

    printf("\n\n/   Updated shop:\t/\n");
    formatShopOutput(&updShop);

    updateShop(&updShop);
  }
}

void updateS() {
  employee updEmployee = getS();
  if (updEmployee.isActive) {
    printf("\\\\ Enter new first name: ");
    fflush(stdin);
    gets(updEmployee.firstName);

    printf("\\\\ Enter new last name: ");
    fflush(stdin);
    gets(updEmployee.lastName);

    printf("\n\n/   Updated employee:\t/\n");
    formatEmployeeOutput(&updEmployee);

    updateEmployee(&updEmployee);
  }
}

void updateShop(const shop *updShop) {
  FILE *shopDataFile = NULL;
  openDbFile(&shopDataFile, shopsData);
  unsigned long shopAddress = getAddressByKey(updShop->id, shopsData);
  fseek(shopDataFile, (long)shopAddress, SEEK_SET);
  fwrite(&*updShop, sizeof(shop), 1, shopDataFile);
  fclose(shopDataFile);
}

void updateEmployee(const employee *updEmployee) {
  FILE *employeeDataFile = NULL;
  openDbFile(&employeeDataFile, employeesData);
  unsigned long employeeAddress =
      getAddressByKey(updEmployee->id, employeesData);
  fseek(employeeDataFile, (long)employeeAddress, SEEK_SET);
  fwrite(&*updEmployee, sizeof(employee), 1, employeeDataFile);
  fclose(employeeDataFile);
}

void updateTrashZone(const trashZone *updTrashZone) {
  FILE *trashZoneFile = NULL;
  openDbFile(&trashZoneFile, trashZoneData);
  fwrite(&*updTrashZone, sizeof(trashZone), 1, trashZoneFile);
  fclose(trashZoneFile);
}