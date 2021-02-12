#pragma pack(1)
#include "dbDeletion.h"
#include "dbRead.h"
#include "dbUpdate.h"

void delM() {
  shop delShop = getM();
  if (delShop.isActive) {
    trashZone trashZone = getTrashZoneData();
    if (delShop.employeeId != -1)
      writeShopEmployeesInactive(&trashZone, &delShop);
    delShop.isActive = false;
    updateShop(&delShop);
    ++trashZone.shopsAmount;
    trashZone.shops[delShop.id - 1] = true;
    updateTrashZone(&trashZone);
    printf("\n\\   Deletion successful\t\\\n");
  }
}

void writeShopEmployeesInactive(trashZone *trashZone, const shop *delShop) {
  employee delEmployee = getEmployeeByKey(delShop->employeeId);
  while (true) {
    ++trashZone->employeesAmount;
    trashZone->employees[delEmployee.id - 1] = true;
    delEmployee.isActive = false;
    updateEmployee(&delEmployee);
    if (delEmployee.nextColleagueId == -1)
      break;
    delEmployee = getEmployeeByKey(delEmployee.nextColleagueId);
  }
}

void delS() {
  employee delEmployee = getS();
  delEmployee.isActive = false;
  updateEmployee(&delEmployee);

  trashZone trashZone = getTrashZoneData();
  ++trashZone.employeesAmount;
  trashZone.employees[delEmployee.id - 1] = true;
  updateTrashZone(&trashZone);

  if (delEmployee.prevColleagueId == -1 && delEmployee.nextColleagueId != -1) {
    shop mShop = getShopByKey(delEmployee.shopId);
    mShop.employeeId = delEmployee.nextColleagueId;
    updateShop(&mShop);
    employee nextEmployee = getEmployeeByKey(delEmployee.nextColleagueId);
    nextEmployee.prevColleagueId = -1;
    updateEmployee(&nextEmployee);
  } else if (delEmployee.prevColleagueId != -1 &&
             delEmployee.nextColleagueId != -1) {
    employee prevColleague = getEmployeeByKey(delEmployee.prevColleagueId);
    prevColleague.nextColleagueId = delEmployee.nextColleagueId;
    updateEmployee(&prevColleague);
  } else {
    employee prevColleague = getEmployeeByKey(delEmployee.prevColleagueId);
    prevColleague.nextColleagueId = -1;
    updateEmployee(&prevColleague);
  }
  printf("\n\\   Deletion successful\t\\\n");
}