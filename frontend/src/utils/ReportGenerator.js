import { saveAs } from 'file-saver';
import * as XLSX from 'xlsx';

export const generatePDF = (data, title) => {
  const doc = new jsPDF();
  doc.text(title, 10, 10);
  doc.autoTable({ html: '#report-table' });
  doc.save(`${title}.pdf`);
};

export const generateExcel = (data, filename) => {
  const worksheet = XLSX.utils.json_to_sheet(data);
  const workbook = XLSX.utils.book_new();
  XLSX.utils.book_append_sheet(workbook, worksheet, 'Sheet1');
  XLSX.writeFile(workbook, `${filename}.xlsx`);
};
