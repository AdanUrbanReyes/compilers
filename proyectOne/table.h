#include <stdio.h>
#ifndef __TABLE_H__
#define __TABLE_H__
typedef struct Table{
	void *object;
	struct Table *up,*down,*left,*right;
}Table;
size_t countRows(Table *header){//header can be header of column
	size_t rows=0;
	while(header!=NULL){
		header=header->down;
		rows++;
	}
	return rows;
}
size_t countColumns(Table *header){//header can be header of row
	size_t columns=0;
	while(header!=NULL){
		header=header->right;
		columns++;
	}
	return columns;
}
size_t *getDimensions(Table *header){
	size_t *dimensions=(size_t *)malloc(sizeof(size_t)*2);//in index cero is row and index one is column
	bzero(dimensions,sizeof(size_t)*2);
	if(header==NULL){
		return dimensions;
	}
	dimensions[0]=countRows(header);
	dimensions[1]=countColumns(header);
	return dimensions;
}
Table *moveToCell(Table *header,size_t row,size_t column){
	
}
Table *createRow(void **objects,size_t columns){//columns represent number of columns for this row (sizeof(objects))
	size_t i;
	Table *auxiliary=NULL,*cell=NULL,*header=NULL;//header of row
	for(i=0;i<columns;i++){
		cell=(Table *)malloc(sizeof(Table));
		bzero(cell,sizeof(Table));
		cell->object=objects[i];
		//code of a list
		if(header==NULL){
			header=cell;
		}else{
			auxiliary=header;
			while(auxiliary->right!=NULL){
				auxiliary=auxiliary->right;
			}
			auxiliary->right=cell;
			cell->left=auxiliary;
		}
		//end code of a list
	}
	return header;
}
Table *createColumn(size_t rows){//rows represent number of rows for this column
	size_t i;
	Table *auxiliary=NULL,*cell=NULL,*header=NULL;//header of row
	for(i=0;i<rows;i++){
		cell=(Table *)malloc(sizeof(Table));
		bzero(cell,sizeof(Table));
		//code of a list
		if(header==NULL){
			header=cell;
		}else{
			auxiliary=header;
			while(auxiliary->down!=NULL){
				auxiliary=auxiliary->down;
			}
			auxiliary->down=cell;
			cell->up=auxiliary;
		}
		//end code of a list
	}
	return header;
}
Table *addRow(Table **header,Table *row){//columns represent number of columns for this row (sizeof(objects))
	if(row==NULL){
		return NULL;
	}
	if(*header==NULL){
		*header=row;
	}else{
		Table *cell=*header;
		while(cell->down!=NULL){
			cell=cell->down;
		}
		while(cell!=NULL&&row!=NULL){
			cell->down=row;
			row->up=cell;
			cell=cell->right;
			row=row->right;
		}
	}
	return row;	
}
Table *addColumn(Table **header,Table *column){//columns represent number of columns for this row (sizeof(objects))
	if(column==NULL){
		return NULL;
	}
	if(*header==NULL){
		*header=column;
	}else{
		Table *cell=*header;
		while(cell->right!=NULL){
			cell=cell->right;
		}
		while(cell!=NULL&&columns!=NULL){
			cell->right=row;
			column->left=cell;
			cell=cell->down;
			column=row->down;
		}
	}
	return row;	
}
#endif
