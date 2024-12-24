import React, { useEffect, useState } from 'react';
import { generatePDF, generateExcel } from '../utils/ReportGenerator';
import { fetchReportData } from '../utils/api';


const ReportsPage = () => {
  const [data, setData] = useState([]);

  useEffect(() => {
    const getData = async () => {
      const reportData = await fetchReportData();
      setData(reportData);
    };
    getData();
  }, []);

  return (
    <div>
      <h2>Reports</h2>
      <button onClick={() => generatePDF(data, 'Fleet Report')}>Download PDF</button>
      <button onClick={() => generateExcel(data, 'Fleet Report')}>Download Excel</button>
    </div>
  );
};

export default ReportsPage;
