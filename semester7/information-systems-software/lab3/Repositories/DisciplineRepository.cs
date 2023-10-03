using System.Data;
using Dapper;

public class DisciplineRepository : IDisciplineRepository
{
    private readonly IDbConnection _db;

    public DisciplineRepository(IDbConnection db)
    {
        _db = db;
    }

    public void Delete(int id)
    {
        _db.Execute("DELETE FROM disciplines WHERE Id = @Id", new { Id = id });
    }

    public IEnumerable<Discipline> GetAll()
    {
        return _db.Query<Discipline>("SELECT * FROM disciplines");
    }

    public Discipline? GetById(int id)
    {
        return _db.QueryFirstOrDefault<Discipline>("SELECT * FROM disciplines WHERE Id = @Id", new { Id = id });
    }

    public int Insert(Discipline obj)
    {
        var sql = @"INSERT INTO disciplines 
        (name, hours, lecture_hours, lab_hours, certification_type)
        VALUES (@Name, @Hours, @LectureHours, @LabHours, 
        Cast(@CertificationType as certification)) RETURNING id;";
        return _db.Query<int>(sql, obj).Single();
    }

    public void Update(Discipline obj)
    {
        var sql = @"UPDATE disciplines SET name = @Name, hours = @Hours, 
        lecture_hours = @LectureHours, lab_hours = @LabHours, 
        certification_type = Cast(@CertificationType as certification)    
        WHERE Id = @Id";
        _db.Query(sql, obj);
    }

    public void Clear()
    {
        _db.Execute("DELETE FROM disciplines");
    }
}