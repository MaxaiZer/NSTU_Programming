using System.Data;

public class DisciplineRepository : IDisciplineRepository
{

    private DataTable _table; 

    public DisciplineRepository(DataSet dataSet)
    {
        var dataTable = new DataTable("disciplines");
        dataTable.Columns.Add("Id", typeof(int));
        dataTable.Columns.Add("Name", typeof(string));
        dataTable.Columns.Add("Hours", typeof(int));
        dataTable.Columns.Add("LectureHours", typeof(int));
        dataTable.Columns.Add("LabHours", typeof(int));
        dataTable.Columns.Add("CertificationType", typeof(string));

         dataSet.Tables.Add(dataTable);
        _table = dataSet.Tables["Disciplines"];  
    }

    public IEnumerable<Discipline> GetAll()
    {
        return _table.AsEnumerable().Select(row => new Discipline
        {
            Id = row.Field<int>("Id"),
            Name = row.Field<string>("Name"),
            Hours = row.Field<int>("Hours"),
            LabHours = row.Field<int>("LabHours"),
            LectureHours = row.Field<int>("LectureHours"),
            CertificationType = row.Field<string>("CertificationType")
        });
    }

    public Discipline? GetById(int id)
    {
        DataRow? foundRow = _table.AsEnumerable()
            .FirstOrDefault(row => row.Field<int>("Id") == id);

        if (foundRow == null) return null;

        return new Discipline
        {
            Id = foundRow.Field<int>("Id"),
            Name = foundRow.Field<string>("Name"),
            Hours = foundRow.Field<int>("Hours"),
            LabHours = foundRow.Field<int>("LabHours"),
            LectureHours = foundRow.Field<int>("LectureHours"),
            CertificationType = foundRow.Field<string>("CertificationType")
        };
    }

    public int Insert(Discipline obj)
    {       
        DataRow newRow = _table.NewRow();
        newRow["Name"] = obj.Name;
        newRow["Hours"] = obj.Hours;
        newRow["LabHours"] = obj.LabHours;
        newRow["LectureHours"] = obj.LectureHours;
        newRow["CertificationType"] = obj.CertificationType;
        
        var id = GetNextId();
        newRow["Id"] = id;

        _table.Rows.Add(newRow);       
        return id;
    }

    public void Update(Discipline obj)
    {
        DataRow? rowToUpdate = _table.AsEnumerable()
            .FirstOrDefault(row => row.Field<int>("Id") == obj.Id);

        if (rowToUpdate == null) return;

        rowToUpdate["Name"] = obj.Name;
        rowToUpdate["Hours"] = obj.Hours;
        rowToUpdate["LabHours"] = obj.LabHours;
        rowToUpdate["LectureHours"] = obj.LectureHours;
        rowToUpdate["CertificationType"] = obj.CertificationType;
    }

    public void Delete(int id)
    {
        DataRow? rowToDelete = _table.AsEnumerable()
            .FirstOrDefault(row => row.Field<int>("Id") == id);

        if (rowToDelete != null)
        {
            _table.Rows.Remove(rowToDelete);
        }
    }

    public void Clear()
    {
        _table.Rows.Clear();
    }

    public void WriteXML(Stream stream)
    {
        _table.WriteXml(stream);
    }

    public void LoadXML(Stream stream)
    {
        _table.ReadXml(stream);
    }

    private int GetNextId()
    {
        if (_table.Rows.Count == 0) return 0;

        int maxId = _table.AsEnumerable().Max(row => row.Field<int>("Id"));
        return maxId + 1;
    }
}