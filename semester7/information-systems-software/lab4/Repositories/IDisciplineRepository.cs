public interface IDisciplineRepository : IGenericRepository<Discipline>
{
    void Clear();

    void WriteXML(Stream stream);

    void LoadXML(Stream stream);
}