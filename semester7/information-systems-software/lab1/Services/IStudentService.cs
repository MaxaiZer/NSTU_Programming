public interface IStudentService
{
    public void Add(Student student);

    public IEnumerable<Student> GetAll();
}