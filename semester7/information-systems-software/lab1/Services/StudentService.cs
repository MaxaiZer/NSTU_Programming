public class StudentService: IStudentService
{
    private List<Student> _list = new();

    public void Add(Student student)
    {
        _list.Add(student);
    }

    public IEnumerable<Student> GetAll()
    {
        return _list;
    }
}