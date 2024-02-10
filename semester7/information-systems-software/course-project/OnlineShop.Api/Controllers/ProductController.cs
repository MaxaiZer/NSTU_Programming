using Microsoft.AspNetCore.Mvc;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Controllers;

[ApiController]
[Route("api/[controller]")]
public class ProductController : ControllerBase
{
    private IProductRepository _repository;

    public ProductController(IProductRepository repository)
    {
        _repository = repository;
    }

    [HttpGet]
    public ActionResult<IEnumerable<Smartphone>> Get(string search = null)
    {
        if (search == null)
            return new JsonResult(_repository.GetAll());
        else
            return new JsonResult(_repository.Search(search));
    }

    [HttpGet("{id}")]
    public IActionResult Get(int id)
    {
        Smartphone? item = _repository.GetById(id);
        if (item == null)
            return NotFound();

        return new JsonResult(item);
    }

    [HttpPost]
    public IActionResult Post([FromBody] Smartphone item)
    {
        _repository.Add(item);
        _repository.Save();
        return Ok();
    }

    [HttpPut("{id}")]
    public IActionResult Put(int id, [FromBody] Smartphone item)
    {

        item.Id = id;
        try
        {
            _repository.Update(item);
            _repository.Save();
        } catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }       
       
        return Ok();
    }

    [HttpDelete("{id}")]
    public IActionResult Delete(int id)
    {
        if (_repository.RemoveById(id))
        {
            _repository.Save();
            return Ok();
        }           

        return NotFound();
    }
}
